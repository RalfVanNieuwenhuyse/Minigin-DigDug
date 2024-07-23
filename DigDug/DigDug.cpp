#include "DigDug.h"
//#include "EventManager.h"
//
//#include <iostream>

rvn::DigDug::DigDug(dae::GameObject* owner)
	:Component(owner)
{
	SetState(PlayerState::Move);	
}

void rvn::DigDug::Update()
{
	m_currentState->Update();
}

void rvn::DigDug::SetState(PlayerState state)
{
	if (m_currentState != nullptr)
		m_currentState->OnExit();
	
	switch (state)
	{
	case rvn::PlayerState::Move:
		m_currentState = std::make_unique<MoveState>(this);
		break;
	case rvn::PlayerState::Pump:
		m_currentState = std::make_unique<PumpState>(this);
		break;
	case rvn::PlayerState::Die:
		m_currentState = std::make_unique<DieState>(this);
		break;
	default:
		break;
	}

	if (m_currentState != nullptr)
		m_currentState->OnEnter();
}

dae::GameObject* rvn::DigDug::GetGameObjectOwner() const
{
	return GetOwner();
}

void rvn::DigDug::ChangeState(const dae::Event*)
{
	//SetState(PlayerState::Die);
}
