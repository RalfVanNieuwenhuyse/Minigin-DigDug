#include "DigDug.h"
#include "Transform.h"
#include "EventManager.h"

//#include <iostream>

rvn::DigDug::DigDug(dae::GameObject* owner)
	:Component(owner)
{
	SetState(PlayerState::Move);	

	auto boundResetLevel = std::bind(&DigDug::ResetLevel, this, std::placeholders::_1);
	dae::GameObjectEvent eventResetLevel;
	eventResetLevel.eventType = "ResetLevel";
	dae::EventManager::GetInstance().AddObserver(eventResetLevel, boundResetLevel);
}

void rvn::DigDug::Update()
{
	m_currentState->Update();

	if(m_IsFirtsFrame)
	{
		m_IsFirtsFrame = false;
		m_FirstPos = GetOwner()->GetTransform()->GetPosition();
	}
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
	case rvn::PlayerState::LoseLife:
		m_currentState = std::make_unique<LifeLostState>(this);
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

void rvn::DigDug::ResetLevel(const dae::Event*)
{
	SetState(PlayerState::Move);
	GetOwner()->GetTransform()->SetPosition(m_FirstPos);
}

