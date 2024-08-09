#include "PookaComp.h"
#include "Transform.h"
#include "EventManager.h"

rvn::PookaComp::PookaComp(dae::GameObject* owner)
	:Component(owner)
{
	SetState(rvn::EPookaState::Attack);

	auto boundResetLevel = std::bind(&PookaComp::ResetLevel, this, std::placeholders::_1);
	dae::GameObjectEvent eventResetLevel;
	eventResetLevel.eventType = "ResetLevel";
	dae::EventManager::GetInstance().AddObserver(eventResetLevel, boundResetLevel);
}

void rvn::PookaComp::Update()
{
	m_currentState->Update();

	if (m_IsFirtsFrame)
	{
		m_IsFirtsFrame = false;
		m_FirstPos = GetOwner()->GetTransform()->GetPosition();
	}
}

void rvn::PookaComp::SetState(EPookaState state)
{
	if (m_currentState != nullptr)
		m_currentState->OnExit();

	switch (state)
	{
	case rvn::EPookaState::Attack:
		m_currentState = std::make_unique<PookaAttackState>(this);
		break;
	case rvn::EPookaState::Ghost:
		m_currentState = std::make_unique<PookaGhostState>(this);
		break;
	case rvn::EPookaState::Pump:
		m_currentState = std::make_unique<PookaPumpState>(this);
		break;
	case rvn::EPookaState::Death:
		m_currentState = std::make_unique<PookaDeathState>(this);
		break;
	default:
		break;
	}

	if (m_currentState != nullptr)
		m_currentState->OnEnter();
}

dae::GameObject* rvn::PookaComp::GetGameObjectOwner() const
{
	return GetOwner();
}

void rvn::PookaComp::ResetLevel(const dae::Event*)
{
	SetState(EPookaState::Attack);
	GetOwner()->GetTransform()->SetPosition(m_FirstPos);
}

