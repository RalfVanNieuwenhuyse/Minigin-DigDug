#include "DigDug.h"
#include "Transform.h"
#include "EventManager.h"
#include "Prefabs.h"

//#include <iostream>

rvn::DigDug::DigDug(dae::GameObject* owner)
	:Component(owner)
{
	SetState(PlayerState::Move);	

	auto boundResetLevel = std::bind(&DigDug::ResetLevel, this, std::placeholders::_1);
	dae::GameObjectEvent eventResetLevel;
	eventResetLevel.eventType = "ResetLevel";
	dae::EventManager::GetInstance().AddObserver(eventResetLevel, boundResetLevel);

	auto pumpright = Prefab::CreatePumpRight(dae::SceneManager::GetInstance().GetActiveScene(),GetOwner()->GetTransform()->GetPosition());
	auto pumpLeft = Prefab::CreatePumpLeft(dae::SceneManager::GetInstance().GetActiveScene(), GetOwner()->GetTransform()->GetPosition());
	auto pumpUp = Prefab::CreatePumpUp(dae::SceneManager::GetInstance().GetActiveScene(), GetOwner()->GetTransform()->GetPosition());
	auto pumpDown = Prefab::CreatePumpDown(dae::SceneManager::GetInstance().GetActiveScene(), GetOwner()->GetTransform()->GetPosition());

	pumpright->SetParent(GetOwner(), true);
	pumpLeft->SetParent(GetOwner(), true);
	pumpUp->SetParent(GetOwner(), true);
	pumpDown->SetParent(GetOwner(), true);

	m_Pumps.push_back(pumpright);
	m_Pumps.push_back(pumpLeft);
	m_Pumps.push_back(pumpUp);
	m_Pumps.push_back(pumpDown);

	for (auto pump : m_Pumps)
	{
		pump->SetActive(false);
	}
}

void rvn::DigDug::Update()
{
	m_currentState->Update();

	if(m_IsFirtsFrame)
	{
		m_IsFirtsFrame = false;
		m_FirstPos = GetOwner()->GetTransform()->GetPosition();
		SetState(PlayerState::Move);
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

