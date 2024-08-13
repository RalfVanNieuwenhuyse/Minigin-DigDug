#include "FygarState.h"
#include "FygarComp.h"
#include "GridMovement.h"
#include "GridComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "EventManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Prefabs.h"
#include "ServiceLocator.h"

#include "GTime.h"
#include "MoveCommand.h"
#include "InputManager.h"
#include "FireCommand.h"

std::mt19937 rvn::FygarAttackState::s_Gen(std::random_device{}());
std::uniform_int_distribution<> rvn::FygarAttackState::s_Distrib(0, 3);

std::mt19937 rvn::FygarFireState::s_GenFygarFire(std::random_device{}());

rvn::FygarState::FygarState(dae::Component* owner)
	:State(owner)
{
}

#pragma region Attack
rvn::FygarAttackState::FygarAttackState(dae::Component* owner)
	: FygarState(owner)
{
}

void rvn::FygarAttackState::OnEnter()
{
	auto OwnerComp = static_cast<FygarComp*>(GetOwnerComponent());
	m_Owner = OwnerComp->GetGameObjectOwner();

	m_MovementComp = m_Owner->GetComponent<GridMovement>().get();
	m_MovementComp->SetSpeed(m_Speed);
	m_MovementComp->ChangeDirection(m_Directions[m_DirectionIndex]);
	m_GridComp = m_MovementComp->GetGridComp();

	auto boundKillDigDug = std::bind(&FygarAttackState::KillDigDug, this, std::placeholders::_1);
	dae::GameObjectEvent eventDigDugKill;
	eventDigDugKill.eventType = "PlayerCollidedEnemy";
	dae::EventManager::GetInstance().AddObserver(eventDigDugKill, boundKillDigDug);

    m_BreathTimer = 0.f;
    std::uniform_real_distribution<> cooldownDis(3.0f, 6.0f);
    m_BreathCooldown = static_cast<float>(cooldownDis(s_Gen));

    if (OwnerComp->IsPlayer2())
    {
        auto& input = dae::InputManager::GetInstance();

        const glm::vec3 moveDirectionHor{ 1, 0, 0 };
        const glm::vec3 moveDirectionVert{ 0, 1, 0 };
        m_LeftCommand = input.AddXboxCommand<rvn::MoveCommandF>(std::make_unique<rvn::MoveCommandF>(m_Owner),
            dae::XboxControllerInput{ 0, dae::XboxController::ControllerButton::DPadLeft, dae::ButtonState::Pressed });
        m_LeftCommand->SetDirection(-moveDirectionHor);

        m_RightCommand = input.AddXboxCommand<rvn::MoveCommandF>(std::make_unique<rvn::MoveCommandF>(m_Owner),
            dae::XboxControllerInput{ 0, dae::XboxController::ControllerButton::DPadRight, dae::ButtonState::Pressed });
        m_RightCommand->SetDirection(moveDirectionHor);

        m_UpCommand = input.AddXboxCommand<rvn::MoveCommandF>(std::make_unique<rvn::MoveCommandF>(m_Owner),
            dae::XboxControllerInput{ 0, dae::XboxController::ControllerButton::DPadUp, dae::ButtonState::Pressed });
        m_UpCommand->SetDirection(-moveDirectionVert);

        m_DownCommand = input.AddXboxCommand<rvn::MoveCommandF>(std::make_unique<rvn::MoveCommandF>(m_Owner),
            dae::XboxControllerInput{ 0, dae::XboxController::ControllerButton::DPadDown, dae::ButtonState::Pressed });
        m_DownCommand->SetDirection(moveDirectionVert);

        m_FireCommand = input.AddXboxCommand<rvn::FireCommand>(std::make_unique<rvn::FireCommand>(m_Owner),
            dae::XboxControllerInput{ 0, dae::XboxController::ControllerButton::ButtonA, dae::ButtonState::Pressed });
    }
}

void rvn::FygarAttackState::OnExit()
{
	auto boundKillDigDug = std::bind(&FygarAttackState::KillDigDug, this, std::placeholders::_1);
	dae::GameObjectEvent eventDigDugKill;
	eventDigDugKill.eventType = "PlayerCollidedEnemy";
	dae::EventManager::GetInstance().RemoveObserver(eventDigDugKill, boundKillDigDug);

    auto& input = dae::InputManager::GetInstance();
    auto OwnerComp = static_cast<FygarComp*>(GetOwnerComponent());
    if (OwnerComp->IsPlayer2())
    {
        input.RemoveXboxCommand(m_UpCommand);
        input.RemoveXboxCommand(m_DownCommand);
        input.RemoveXboxCommand(m_LeftCommand);
        input.RemoveXboxCommand(m_RightCommand);
        input.RemoveXboxCommand(m_FireCommand);
    }
}

void rvn::FygarAttackState::Update()
{
    auto OwnerComp = static_cast<FygarComp*>(GetOwnerComponent());
    if (!OwnerComp->IsPlayer2())
    {
        bool directionHasChanged = false;
        bool validDirection = false;

        auto tempPos = m_Owner->GetTransform()->GetPosition();
        tempPos.x += 8;
        tempPos.y += 8;

        auto checkPos = tempPos + (m_Directions[m_DirectionIndex] * 10.f);

        validDirection = m_GridComp->IsCellDug(checkPos) && m_GridComp->IsWithinGridBounds(checkPos);

        std::uniform_real_distribution<> chanceDist(0.0, 1.0);
        double changeChance = chanceDist(s_Gen);

        if (!validDirection || changeChance < 0.025)
        {
            // Get the opposite direction index
            int oppositeDirectionIndex = (m_DirectionIndex + 2) % 4;
            std::vector<int> potentialDirections;

            for (int i = 0; i < static_cast<int>(m_Directions.size()); ++i)
            {
                if (i != oppositeDirectionIndex)
                {
                    potentialDirections.push_back(i);
                }
            }

            if (!potentialDirections.empty())
            {
                std::uniform_int_distribution<> dist(0, static_cast<int>(potentialDirections.size()) - 1);
                int randomIndex = dist(s_Gen);
                int dirIndex = potentialDirections[randomIndex];

                checkPos = tempPos + (m_Directions[dirIndex] * 10.f);
                validDirection = m_GridComp->IsCellDug(checkPos) && m_GridComp->IsWithinGridBounds(checkPos);

                if (validDirection)
                {
                    m_DirectionIndex = dirIndex;
                    directionHasChanged = true;
                }
            }
        }

        if (directionHasChanged)
        {
            m_MovementComp->ChangeDirection(m_Directions[m_DirectionIndex]);
        }

        m_MovementComp->Move();

        m_BreathTimer += dae::GTime::GetInstance().GetDeltaTime();

        if (m_BreathTimer >= m_BreathCooldown)
        {
            m_BreathTimer = 0.f;
            std::uniform_real_distribution<> cooldownDis(3.0f, 6.0f);
            m_BreathCooldown = static_cast<float>(cooldownDis(s_Gen));

            //auto OwnerComp = static_cast<FygarComp*>(GetOwnerComponent());
            OwnerComp->SetState(EFygarState::Fire);
        }
    }
    else
    {

    }
}

void rvn::FygarAttackState::Exicute()
{
    auto OwnerComp = static_cast<FygarComp*>(GetOwnerComponent());
    OwnerComp->SetState(EFygarState::Fire);
}

void rvn::FygarAttackState::KillDigDug(const dae::Event* e)
{
    if (const dae::GameObjectEvent* GameEvent = static_cast<const dae::GameObjectEvent*>(e))
    {
        std::shared_ptr<dae::GameObjectEvent> eventDamageDigDug = std::make_shared<dae::GameObjectEvent>();
        eventDamageDigDug->eventType = "DamageDigDug";
        eventDamageDigDug->gameObject = GameEvent->gameObject;
        dae::EventManager::GetInstance().SendEventMessage(std::move(eventDamageDigDug));
    }
}
#pragma endregion

#pragma region Fire
rvn::FygarFireState::FygarFireState(dae::Component* owner)
	: FygarState(owner)
{
}

void rvn::FygarFireState::OnEnter()
{
    auto OwnerComp = static_cast<FygarComp*>(GetOwnerComponent());
    auto ownerGO = OwnerComp->GetGameObjectOwner();
    dae::servicelocator::get_sound_system().Play(dae::SoundData{ 2, 1 });

    if (!OwnerComp->IsPlayer2())
    {
        std::uniform_real_distribution<> directionDis(0, 3);
        int randomDirection = static_cast<int>(directionDis(s_GenFygarFire));
        switch (randomDirection)
        {
        case 0:
            Prefab::CreateFireBreathRight(dae::SceneManager::GetInstance().GetActiveScene(), ownerGO->GetTransform()->GetPosition());
            break;
        case 1:
            Prefab::CreateFireBreathLeft(dae::SceneManager::GetInstance().GetActiveScene(), ownerGO->GetTransform()->GetPosition());
            break;
        case 2:
            Prefab::CreateFireBreathUp(dae::SceneManager::GetInstance().GetActiveScene(), ownerGO->GetTransform()->GetPosition());
            break;
        case 3:
            Prefab::CreateFireBreathDown(dae::SceneManager::GetInstance().GetActiveScene(), ownerGO->GetTransform()->GetPosition());
            break;
        default:
            break;
        }
    }
    
    if (OwnerComp->IsPlayer2())
    {
        if (OwnerComp->GetLastDirection() == glm::vec3{ 1,0,0 })
        {
            Prefab::CreateFireBreathRight(dae::SceneManager::GetInstance().GetActiveScene(), ownerGO->GetTransform()->GetPosition());
        }
        else if (OwnerComp->GetLastDirection() == glm::vec3{ -1,0,0 })
        {
            Prefab::CreateFireBreathLeft(dae::SceneManager::GetInstance().GetActiveScene(), ownerGO->GetTransform()->GetPosition());
        }
        else if (OwnerComp->GetLastDirection() == glm::vec3{ 0,1,0 })
        {
            Prefab::CreateFireBreathDown(dae::SceneManager::GetInstance().GetActiveScene(), ownerGO->GetTransform()->GetPosition());

        }
        else if (OwnerComp->GetLastDirection() == glm::vec3{ 0,-1,0 })
        {
            Prefab::CreateFireBreathUp(dae::SceneManager::GetInstance().GetActiveScene(), ownerGO->GetTransform()->GetPosition());
        }
        else
        {
            Prefab::CreateFireBreathRight(dae::SceneManager::GetInstance().GetActiveScene(), ownerGO->GetTransform()->GetPosition());
        }
    }
}

void rvn::FygarFireState::OnExit()
{
}

void rvn::FygarFireState::Update()
{
    m_Timer += dae::GTime::GetInstance().GetDeltaTime();
    if (m_MaxTime <= m_Timer)
    {
        m_Timer = 0;
        auto OwnerComp = static_cast<FygarComp*>(GetOwnerComponent());
        OwnerComp->SetState(EFygarState::Attack);
    }
}
#pragma endregion

#pragma region Ghost
rvn::FygarGhostState::FygarGhostState(dae::Component* owner)
	:FygarState(owner)
{
}

void rvn::FygarGhostState::OnEnter()
{
}

void rvn::FygarGhostState::OnExit()
{
}

void rvn::FygarGhostState::Update()
{
}
#pragma endregion

#pragma region Pump
rvn::FygarPumpState::FygarPumpState(dae::Component* owner)
	:FygarState(owner)
{
}

void rvn::FygarPumpState::OnEnter()
{
}

void rvn::FygarPumpState::OnExit()
{
}

void rvn::FygarPumpState::Update()
{
}
#pragma endregion

#pragma region Death
rvn::FygarDieState::FygarDieState(dae::Component* owner)
	:FygarState(owner)
{
}

void rvn::FygarDieState::OnEnter()
{
}

void rvn::FygarDieState::OnExit()
{
}

void rvn::FygarDieState::Update()
{
}
#pragma endregion