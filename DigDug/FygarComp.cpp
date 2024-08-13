#include "FygarComp.h"
#include "Transform.h"
#include "EventManager.h"

rvn::FygarComp::FygarComp(dae::GameObject* owner)
	:Component(owner)
{
	SetState(EFygarState::Attack);

	auto boundResetLevel = std::bind(&FygarComp::ResetLevel, this, std::placeholders::_1);
	dae::GameObjectEvent eventResetLevel;
	eventResetLevel.eventType = "ResetLevel";
	dae::EventManager::GetInstance().AddObserver(eventResetLevel, boundResetLevel);
}

void rvn::FygarComp::Update()
{
	m_currentState->Update();

	if (m_IsFirtsFrame)
	{
		m_IsFirtsFrame = false;
		m_FirstPos = GetOwner()->GetTransform()->GetPosition();
		SetState(EFygarState::Attack);
	}
}

void rvn::FygarComp::SetState(EFygarState state)
{
	if (m_currentState != nullptr)
		m_currentState->OnExit();

	switch (state)
	{
	case rvn::EFygarState::Attack:
		m_currentState = std::make_unique<FygarAttackState>(this);
		break;
	case rvn::EFygarState::Fire:
		m_currentState = std::make_unique<FygarFireState>(this);
		break;
	case rvn::EFygarState::Ghost:
		m_currentState = std::make_unique<FygarGhostState>(this);
		break;
	case rvn::EFygarState::Pump:
		m_currentState = std::make_unique<FygarPumpState>(this);
		break;
	case rvn::EFygarState::Death:
		m_currentState = std::make_unique<FygarDieState>(this);
		break;
	default:
		break;
	}

	if (m_currentState != nullptr)
		m_currentState->OnEnter();
}

dae::GameObject* rvn::FygarComp::GetGameObjectOwner() const
{
	return GetOwner();
}

void rvn::FygarComp::Exicute()
{
	m_currentState->Exicute();
}

void rvn::FygarComp::ResetLevel(const dae::Event*)
{
	SetState(EFygarState::Attack);
	GetOwner()->GetTransform()->SetPosition(m_FirstPos);
}
