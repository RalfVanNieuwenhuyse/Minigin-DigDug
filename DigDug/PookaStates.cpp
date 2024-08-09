#include "PookaStates.h"
#include "PookaComp.h"
#include "GridMovement.h"
#include "GridComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "EventManager.h"

#include <iostream>


std::mt19937 rvn::PookaAttackState::s_Gen(std::random_device{}());
std::uniform_int_distribution<> rvn::PookaAttackState::s_Distrib(0, 3);

rvn::PookaStates::PookaStates(dae::Component* owner)
	:State(owner)
{
}

#pragma region Attack
rvn::PookaAttackState::PookaAttackState(dae::Component* owner)
	: PookaStates(owner)
{
}

void rvn::PookaAttackState::OnEnter()
{
	auto OwnerComp = static_cast<PookaComp*>(GetOwnerComponent());
	m_Owner = OwnerComp->GetGameObjectOwner();

	m_MovementComp = m_Owner->GetComponent<GridMovement>().get();
	m_MovementComp->SetSpeed(m_Speed);
	m_MovementComp->ChangeDirection(m_Directions[m_DirectionIndex]);
	m_GridComp = m_MovementComp->GetGridComp();

    auto boundKillDigDug = std::bind(&PookaAttackState::KillDigDug, this, std::placeholders::_1);
    dae::GameObjectEvent eventDigDugKill;
    eventDigDugKill.eventType = "PlayerCollidedEnemy";
    dae::EventManager::GetInstance().AddObserver(eventDigDugKill, boundKillDigDug);
}

void rvn::PookaAttackState::OnExit()
{
    auto boundKillDigDug = std::bind(&PookaAttackState::KillDigDug, this, std::placeholders::_1);
    dae::GameObjectEvent eventDigDugKill;
    eventDigDugKill.eventType = "PlayerCollidedEnemy";
    dae::EventManager::GetInstance().RemoveObserver(eventDigDugKill, boundKillDigDug);
}

void rvn::PookaAttackState::Update()
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
}
void rvn::PookaAttackState::KillDigDug(const dae::Event* e)
{
    if (const dae::GameObjectEvent* GameEvent = static_cast<const dae::GameObjectEvent*>(e))
    {
        std::unique_ptr<dae::GameObjectEvent> eventDamageDigDug = std::make_unique<dae::GameObjectEvent>();
        eventDamageDigDug->eventType = "DamageDigDug";
        eventDamageDigDug->gameObject = GameEvent->gameObject;
        dae::EventManager::GetInstance().SendEventMessage(std::move(eventDamageDigDug));
    }
}
#pragma endregion

#pragma region Ghost
rvn::PookaGhostState::PookaGhostState(dae::Component* owner)
	: PookaStates(owner)
{
}

void rvn::PookaGhostState::OnEnter()
{
}

void rvn::PookaGhostState::OnExit()
{
}

void rvn::PookaGhostState::Update()
{
}
#pragma endregion

#pragma region Pump
rvn::PookaPumpState::PookaPumpState(dae::Component* owner)
	:PookaStates(owner)
{
}

void rvn::PookaPumpState::OnEnter()
{
}

void rvn::PookaPumpState::OnExit()
{
}

void rvn::PookaPumpState::Update()
{
}
#pragma endregion

#pragma region Death
rvn::PookaDeathState::PookaDeathState(dae::Component* owner)
	:PookaStates(owner)
{
}

void rvn::PookaDeathState::OnEnter()
{
}

void rvn::PookaDeathState::OnExit()
{
}

void rvn::PookaDeathState::Update()
{
}
#pragma endregion