#include "DebugCommands.h"
#include "LivesComponent.h"
#include "PlayerScore.h"
#include "EventManager.h"

dae::RemoveLifeCommand::RemoveLifeCommand(GameObject* gameObject)
	:GameObjectCommand(gameObject)
{
	m_Lives = GetGameObject()->GetComponent<LivesComponent>();
}

void dae::RemoveLifeCommand::Execute()
{
	m_Lives->RemoveLives();
}

dae::AddScoreCommand::AddScoreCommand(GameObject* gameObject)
	:GameObjectCommand(gameObject)
{
	m_ScoreComp = GetGameObject()->GetComponent<PlayerScore>();
}

void dae::AddScoreCommand::Execute()
{
	m_ScoreComp->AddScore(100);
}

dae::EatBoostCommand::EatBoostCommand(GameObject* gameObject)
	:GameObjectCommand(gameObject)
{
}

void dae::EatBoostCommand::Execute()
{
	std::unique_ptr<GameObjectEvent> event = std::make_unique<GameObjectEvent>();
	event->eventType = "EatenBoost";
	event->gameObject = GetGameObject();
	EventManager::GetInstance().SendEventMessage(std::move(event));
}
