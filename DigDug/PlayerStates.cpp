#include "PlayerStates.h"
#include "MoveCommand.h"
#include "InputManager.h"
#include "DigDug.h"
#include "Transform.h"
#include "SceneManager.h"

#include <iostream>

rvn::PlayerStates::PlayerStates(dae::Component* owner)
	:State(owner)
{
}

rvn::MoveState::MoveState(dae::Component* owner)
	:PlayerStates(owner)
{
    
}

void rvn::MoveState::OnEnter()
{
    auto DigDugComp = dynamic_cast<DigDug*>(GetOwnerComponent());
    auto player = DigDugComp->GetGameObjectOwner();

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
}

void rvn::MoveState::OnExit()
{
    auto& input = dae::InputManager::GetInstance();
    input.RemoveKeyboardCommand(m_UpCommand);
    input.RemoveKeyboardCommand(m_DownCommand);
    input.RemoveKeyboardCommand(m_LeftCommand);
    input.RemoveKeyboardCommand(m_RightCommand);
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

rvn::PumpState::PumpState(dae::Component* owner)
	:PlayerStates(owner)
{
}

void rvn::PumpState::OnEnter()
{
}

void rvn::PumpState::OnExit()
{
}

void rvn::PumpState::Update()
{
}

rvn::DieState::DieState(dae::Component* owner)
	:PlayerStates(owner)
{
}

void rvn::DieState::OnEnter()
{
}

void rvn::DieState::OnExit()
{
}

void rvn::DieState::Update()
{
}
