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
    player->GetComponent<dae::Image>()->SetTexture("Characters/DigDug01.png");

    auto& input = dae::InputManager::GetInstance();

    const glm::vec3 moveDirectionHor{ 1, 0, 0 };
    const glm::vec3 moveDirectionVert{ 0, 1, 0 };

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

    auto boundKillDigDug = std::bind(&MoveState::DamageDigDug, this, std::placeholders::_1);
    dae::GameObjectEvent eventDigDugKill;
    eventDigDugKill.eventType = "DamageDigDug";
    dae::EventManager::GetInstance().AddObserver(eventDigDugKill, boundKillDigDug);
}

void rvn::MoveState::OnExit()
{
    auto& input = dae::InputManager::GetInstance();
    input.RemoveKeyboardCommand(m_UpCommand);
    input.RemoveKeyboardCommand(m_DownCommand);
    input.RemoveKeyboardCommand(m_LeftCommand);
    input.RemoveKeyboardCommand(m_RightCommand);

    auto boundKillDigDug = std::bind(&MoveState::DamageDigDug, this, std::placeholders::_1);
    dae::GameObjectEvent eventDigDugKill;
    eventDigDugKill.eventType = "DamageDigDug";
    dae::EventManager::GetInstance().RemoveObserver(eventDigDugKill, boundKillDigDug);
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
#pragma endregion MoveState

#pragma region PumpState

rvn::PumpState::PumpState(dae::Component* owner)
	:PlayerStates(owner)
{
}

void rvn::PumpState::OnEnter()
{
    auto boundKillDigDug = std::bind(&PumpState::DamageDigDug, this, std::placeholders::_1);
    dae::GameObjectEvent eventDigDugKill;
    eventDigDugKill.eventType = "DamageDigDug";
    dae::EventManager::GetInstance().AddObserver(eventDigDugKill, boundKillDigDug);
}

void rvn::PumpState::OnExit()
{
    auto boundKillDigDug = std::bind(&PumpState::DamageDigDug, this, std::placeholders::_1);
    dae::GameObjectEvent eventDigDugKill;
    eventDigDugKill.eventType = "DamageDigDug";
    dae::EventManager::GetInstance().RemoveObserver(eventDigDugKill, boundKillDigDug);
}

void rvn::PumpState::Update()
{
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
#pragma endregion PumpState

#pragma region DieState

rvn::DieState::DieState(dae::Component* owner)
    :PlayerStates(owner)
{
}

void rvn::DieState::OnEnter()
{
    std::unique_ptr<dae::Event> GameOver = std::make_unique<dae::Event>();
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
}

void rvn::LifeLostState::OnExit()
{
    auto DigDugComp = dynamic_cast<DigDug*>(GetOwnerComponent());
    auto player = DigDugComp->GetGameObjectOwner();
    auto livescomp = player->GetComponent<dae::LivesComponent>();

    if (livescomp->GetLives() > 0)
    {
        std::unique_ptr<dae::Event> eventResetLvl = std::make_unique<dae::Event>();
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