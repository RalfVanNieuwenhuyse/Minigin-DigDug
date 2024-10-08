#include "PlayerStates.h"
#include "MoveCommand.h"
#include "InputManager.h"
#include "DigDug.h"
#include "Transform.h"
#include "SceneManager.h"
#include "EventManager.h"
#include <iostream>
#include "LivesComponent.h"
#include "GTime.h"

#include "Image.h"
#include "ServiceLocator.h"

#include "Prefabs.h"
#include "SceneManager.h"
#include "Scene.h"

#include "DistructionComponent.h"

rvn::PlayerStates::PlayerStates(dae::Component* owner)
	:State(owner)
{
}


#pragma region MoveState

rvn::MoveState::MoveState(dae::Component* owner)
	:PlayerStates(owner)
{
    
}

void rvn::MoveState::OnEnter()
{
    auto DigDugComp = dynamic_cast<DigDug*>(GetOwnerComponent());
    auto player = DigDugComp->GetGameObjectOwner();
    if (!DigDugComp->IsPlayer2())
    {
        player->GetComponent<dae::Image>()->SetTexture("Characters/DigDug01.png");
    }
    else
    {
        player->GetComponent<dae::Image>()->SetTexture("Characters/DigDug02.png");
    }

   

    auto& input = dae::InputManager::GetInstance();

    const glm::vec3 moveDirectionHor{ 1, 0, 0 };
    const glm::vec3 moveDirectionVert{ 0, 1, 0 };

    if(!DigDugComp->IsPlayer2())
    {
        m_LeftCommand = input.AddKeyboardCommand<rvn::MoveCommand>(std::make_unique<rvn::MoveCommand>(player),
            dae::KeyboardInput{ SDL_SCANCODE_A, dae::ButtonState::Pressed });
        m_LeftCommand->SetDirection(-moveDirectionHor);

        m_RightCommand = input.AddKeyboardCommand<rvn::MoveCommand>(std::make_unique<rvn::MoveCommand>(player),
            dae::KeyboardInput{ SDL_SCANCODE_D, dae::ButtonState::Pressed });
        m_RightCommand->SetDirection(moveDirectionHor);

        m_UpCommand = input.AddKeyboardCommand<rvn::MoveCommand>(std::make_unique<rvn::MoveCommand>(player),
            dae::KeyboardInput{ SDL_SCANCODE_W, dae::ButtonState::Pressed });
        m_UpCommand->SetDirection(-moveDirectionVert);

        m_DownCommand = input.AddKeyboardCommand<rvn::MoveCommand>(std::make_unique<rvn::MoveCommand>(player),
            dae::KeyboardInput{ SDL_SCANCODE_S, dae::ButtonState::Pressed });
        m_DownCommand->SetDirection(moveDirectionVert);
    }

    if (DigDugComp->IsPlayer2())
    {
        m_LeftCommand = input.AddXboxCommand<rvn::MoveCommand>(std::make_unique<rvn::MoveCommand>(player),
            dae::XboxControllerInput{ 0, dae::XboxController::ControllerButton::DPadLeft, dae::ButtonState::Pressed });
        m_LeftCommand->SetDirection(-moveDirectionHor);        

        m_RightCommand = input.AddXboxCommand<rvn::MoveCommand>(std::make_unique<rvn::MoveCommand>(player),
            dae::XboxControllerInput{ 0, dae::XboxController::ControllerButton::DPadRight, dae::ButtonState::Pressed });
        m_RightCommand->SetDirection(moveDirectionHor);

        m_UpCommand = input.AddXboxCommand<rvn::MoveCommand>(std::make_unique<rvn::MoveCommand>(player),
            dae::XboxControllerInput{ 0, dae::XboxController::ControllerButton::DPadUp, dae::ButtonState::Pressed });
        m_UpCommand->SetDirection(-moveDirectionVert);

        m_DownCommand = input.AddXboxCommand<rvn::MoveCommand>(std::make_unique<rvn::MoveCommand>(player),
            dae::XboxControllerInput{ 0, dae::XboxController::ControllerButton::DPadDown, dae::ButtonState::Pressed });
        m_DownCommand->SetDirection(moveDirectionVert);
    }

    auto boundKillDigDug = std::bind(&MoveState::DamageDigDug, this, std::placeholders::_1);
    dae::GameObjectEvent eventDigDugKill;
    eventDigDugKill.eventType = "DamageDigDug";
    dae::EventManager::GetInstance().AddObserver(eventDigDugKill, boundKillDigDug);

    auto boundPump = std::bind(&MoveState::SetToPump, this, std::placeholders::_1);
    dae::GameObjectEvent eventPump;
    eventPump.eventType = "PumpCommand";
    dae::EventManager::GetInstance().AddObserver(eventPump, boundPump);
}

void rvn::MoveState::OnExit()
{
    auto DigDugComp = dynamic_cast<DigDug*>(GetOwnerComponent());
    auto& input = dae::InputManager::GetInstance();
    if (!DigDugComp->IsPlayer2())
    {
        input.RemoveKeyboardCommand(m_UpCommand);
        input.RemoveKeyboardCommand(m_DownCommand);
        input.RemoveKeyboardCommand(m_LeftCommand);
        input.RemoveKeyboardCommand(m_RightCommand);
    }
    if (DigDugComp->IsPlayer2())
    {
        input.RemoveXboxCommand(m_UpCommand);
        input.RemoveXboxCommand(m_DownCommand);
        input.RemoveXboxCommand(m_LeftCommand);
        input.RemoveXboxCommand(m_RightCommand);
    }

    auto boundKillDigDug = std::bind(&MoveState::DamageDigDug, this, std::placeholders::_1);
    dae::GameObjectEvent eventDigDugKill;
    eventDigDugKill.eventType = "DamageDigDug";
    dae::EventManager::GetInstance().RemoveObserver(eventDigDugKill, boundKillDigDug);

    auto boundPump = std::bind(&MoveState::SetToPump, this, std::placeholders::_1);
    dae::GameObjectEvent eventPump;
    eventPump.eventType = "PumpCommand";
    dae::EventManager::GetInstance().RemoveObserver(eventPump, boundPump);
}

void rvn::MoveState::Update()
{
    auto DigDugComp = dynamic_cast<DigDug*>(GetOwnerComponent());
    auto player = DigDugComp->GetGameObjectOwner();
    auto currentPos =  player->GetTransform()->GetPosition();
    if (m_OldPos == currentPos)return;
    m_OldPos = currentPos;
    auto tempPos = currentPos;
    tempPos.x += 8;
    tempPos.y += 8;
    player->GetComponent<rvn::GridMovement>()->GetGridComp()->DigCell(tempPos, dae::SceneManager::GetInstance().GetActiveScene());
}

void rvn::MoveState::DamageDigDug(const dae::Event* e)
{
    if (const dae::GameObjectEvent* GameEvent = static_cast<const dae::GameObjectEvent*>(e))
    {
        auto DigDugComp = dynamic_cast<DigDug*>(GetOwnerComponent());
        auto player = DigDugComp->GetGameObjectOwner();
        if (player == GameEvent->gameObject)
        {
            DigDugComp->SetState(PlayerState::LoseLife);
        }
    }
}
void rvn::MoveState::SetToPump(const dae::Event* e)
{
    if (const dae::GameObjectEvent* GameEvent = static_cast<const dae::GameObjectEvent*>(e))
    {
        auto DigDugComp = dynamic_cast<DigDug*>(GetOwnerComponent());
        auto player = DigDugComp->GetGameObjectOwner();
        if (player == GameEvent->gameObject)
        {
            DigDugComp->SetState(PlayerState::Pump);
        }
    }
}
#pragma endregion MoveState

#pragma region PumpState

rvn::PumpState::PumpState(dae::Component* owner)
	:PlayerStates(owner)
{
}

void rvn::PumpState::OnEnter()
{
    auto DigDugComp = dynamic_cast<DigDug*>(GetOwnerComponent());
    auto player = DigDugComp->GetGameObjectOwner();
    if (!DigDugComp->IsPlayer2())
    {
        player->GetComponent<dae::Image>()->SetTexture("Characters/DigDugPump01.png");
    }
    else
    {
        player->GetComponent<dae::Image>()->SetTexture("Characters/DigDugPump02.png");
    }

    auto boundKillDigDug = std::bind(&PumpState::DamageDigDug, this, std::placeholders::_1);
    dae::GameObjectEvent eventDigDugKill;
    eventDigDugKill.eventType = "DamageDigDug";
    dae::EventManager::GetInstance().AddObserver(eventDigDugKill, boundKillDigDug);

    auto boundPump = std::bind(&PumpState::Pump, this, std::placeholders::_1);
    dae::GameObjectEvent eventPump;
    eventPump.eventType = "PumpCommand";
    dae::EventManager::GetInstance().AddObserver(eventPump, boundPump);

    auto boundHit = std::bind(&PumpState::EnemyHit, this, std::placeholders::_1);
    dae::GameObjectEvent eventHit;
    eventHit.eventType = "PumpHitEnenmy";
    dae::EventManager::GetInstance().AddObserver(eventHit, boundHit);

    auto OwnerComp = static_cast<DigDug*>(GetOwnerComponent());
    //auto ownerGO = OwnerComp->GetGameObjectOwner();

    if (OwnerComp->GetLastDirection() == glm::vec3{1,0,0})
    {
        //m_Pump = Prefab::CreatePumpRight(dae::SceneManager::GetInstance().GetActiveScene(), ownerGO->GetTransform()->GetPosition());
        OwnerComp->GetPumps()[0]->SetActive(true);
    }
    else if(OwnerComp->GetLastDirection() == glm::vec3{ -1,0,0 })
    {
        //m_Pump = Prefab::CreatePumpLeft(dae::SceneManager::GetInstance().GetActiveScene(), ownerGO->GetTransform()->GetPosition());
        OwnerComp->GetPumps()[1]->SetActive(true);
    }
    else if (OwnerComp->GetLastDirection() == glm::vec3{ 0,1,0 })
    {
        //m_Pump = Prefab::CreatePumpDown(dae::SceneManager::GetInstance().GetActiveScene(), ownerGO->GetTransform()->GetPosition());
        OwnerComp->GetPumps()[3]->SetActive(true);
    }
    else if (OwnerComp->GetLastDirection() == glm::vec3{ 0,-1,0 })
    {
        //m_Pump = Prefab::CreatePumpUp(dae::SceneManager::GetInstance().GetActiveScene(), ownerGO->GetTransform()->GetPosition());
        OwnerComp->GetPumps()[2]->SetActive(true);
    }
    else
    {
        //m_Pump = Prefab::CreatePumpRight(dae::SceneManager::GetInstance().GetActiveScene(), ownerGO->GetTransform()->GetPosition());
        OwnerComp->GetPumps()[0]->SetActive(true);
    }

    dae::servicelocator::get_sound_system().Play(dae::SoundData{ 3, 1 });    
}

void rvn::PumpState::OnExit()
{
    auto boundKillDigDug = std::bind(&PumpState::DamageDigDug, this, std::placeholders::_1);
    dae::GameObjectEvent eventDigDugKill;
    eventDigDugKill.eventType = "DamageDigDug";
    dae::EventManager::GetInstance().RemoveObserver(eventDigDugKill, boundKillDigDug);

    auto boundPump = std::bind(&PumpState::Pump, this, std::placeholders::_1);
    dae::GameObjectEvent eventPump;
    eventPump.eventType = "PumpCommand";
    dae::EventManager::GetInstance().RemoveObserver(eventPump, boundPump);

    auto boundHit = std::bind(&PumpState::EnemyHit, this, std::placeholders::_1);
    dae::GameObjectEvent eventHit;
    eventHit.eventType = "PumpHitEnenmy";
    dae::EventManager::GetInstance().RemoveObserver(eventHit, boundHit);

    //m_Pump->Destroy();
    auto OwnerComp = static_cast<DigDug*>(GetOwnerComponent());
    for (auto pump : OwnerComp->GetPumps())
    {
        pump->SetActive(false);
    }   

    m_HitEnemy = false;
}

void rvn::PumpState::Update()
{
    m_IdleTimer += dae::GTime::GetInstance().GetDeltaTime();
    m_CDTimer += dae::GTime::GetInstance().GetDeltaTime();

    if (m_IdleTimer >= m_MaxPumpIdle)
    {
        auto DigDugComp = dynamic_cast<DigDug*>(GetOwnerComponent());
        DigDugComp->SetState(PlayerState::Move);
    }
}

void rvn::PumpState::DamageDigDug(const dae::Event* e)
{
    if (const dae::GameObjectEvent* GameEvent = static_cast<const dae::GameObjectEvent*>(e))
    {
        auto DigDugComp = dynamic_cast<DigDug*>(GetOwnerComponent());
        auto player = DigDugComp->GetGameObjectOwner();
        if (player == GameEvent->gameObject)
        {
            DigDugComp->SetState(PlayerState::LoseLife);
        }
    }
}
void rvn::PumpState::Pump(const dae::Event* e)
{
    if (const dae::GameObjectEvent* GameEvent = static_cast<const dae::GameObjectEvent*>(e))
    {
        auto DigDugComp = dynamic_cast<DigDug*>(GetOwnerComponent());
        auto player = DigDugComp->GetGameObjectOwner();
        if (player == GameEvent->gameObject)
        {       
            m_IdleTimer = 0;
            //m_Pump->GetComponent< rvn::DistructionComponent>()->ResetTimer();
            if (m_CDTimer >= m_CoolDown && m_HitEnemy)
            {                
                std::shared_ptr<dae::GameObjectEvent> eventPumping = std::make_shared<dae::GameObjectEvent>();
                eventPumping->eventType = "Pumping";
                eventPumping->gameObject = GameEvent->gameObject;
                dae::EventManager::GetInstance().SendEventMessage(std::move(eventPumping));

            }
        }
    }
}
void rvn::PumpState::EnemyHit(const dae::Event*)
{
    m_HitEnemy = true;
}
#pragma endregion PumpState

#pragma region DieState

rvn::DieState::DieState(dae::Component* owner)
    :PlayerStates(owner)
{
}

void rvn::DieState::OnEnter()
{
    std::shared_ptr<dae::Event> GameOver = std::make_shared<dae::Event>();
    GameOver->eventType = "GameOver";
    dae::EventManager::GetInstance().SendEventMessage(std::move(GameOver));

    dae::servicelocator::get_sound_system().Play(dae::SoundData{ 1, 1 });
}

void rvn::DieState::OnExit()
{
}

void rvn::DieState::Update()
{
}
#pragma endregion DieState

#pragma region LifeLostState
rvn::LifeLostState::LifeLostState(dae::Component* owner)
    :PlayerStates(owner)
{
}

void rvn::LifeLostState::OnEnter()
{
    auto DigDugComp = dynamic_cast<DigDug*>(GetOwnerComponent());
    auto player = DigDugComp->GetGameObjectOwner();
    auto livescomp = player->GetComponent<dae::LivesComponent>();
    if (livescomp) { livescomp->RemoveLives(); }
    player->GetComponent<dae::Image>()->SetTexture("Characters/DigDugDeath01.png");

    if (!DigDugComp->IsPlayer2())
    {
        player->GetComponent<dae::Image>()->SetTexture("Characters/DigDugDeath01.png");
    }
    else
    {
        player->GetComponent<dae::Image>()->SetTexture("Characters/DigDugDeath02.png");
    }
}

void rvn::LifeLostState::OnExit()
{
    auto DigDugComp = dynamic_cast<DigDug*>(GetOwnerComponent());
    auto player = DigDugComp->GetGameObjectOwner();
    auto livescomp = player->GetComponent<dae::LivesComponent>();

    if (livescomp->GetLives() > 0)
    {
        std::shared_ptr<dae::Event> eventResetLvl = std::make_shared<dae::Event>();
        eventResetLvl->eventType = "ResetLevel";
        dae::EventManager::GetInstance().SendEventMessage(std::move(eventResetLvl));
    }   
}

void rvn::LifeLostState::Update()
{
    m_Timer += dae::GTime::GetInstance().GetDeltaTime();
    if (m_MaxTime <= m_Timer)
    {
        auto DigDugComp = dynamic_cast<DigDug*>(GetOwnerComponent());
        auto player = DigDugComp->GetGameObjectOwner();
        auto livescomp = player->GetComponent<dae::LivesComponent>();
        
        if (livescomp->GetLives() <= 0)
        {
            DigDugComp->SetState(PlayerState::Die);
        }
        else
        {
            DigDugComp->SetState(PlayerState::Move);
        }
    }
}
#pragma endregion LifeLostState