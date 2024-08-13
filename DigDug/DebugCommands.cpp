#include "DebugCommands.h"
#include "LivesComponent.h"
#include "PlayerScore.h"
#include "EventManager.h"
#include "GameMode.h"

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
	std::shared_ptr<GameObjectEvent> event = std::make_shared<GameObjectEvent>();
	event->eventType = "EatenBoost";
	event->gameObject = GetGameObject();
	EventManager::GetInstance().SendEventMessage(std::move(event));
}

dae::NextLevelCommand::NextLevelCommand()
	:Command()
{
}

void dae::NextLevelCommand::Execute()
{
	rvn::GameMode::GetInstance().NextLevel();
}

dae::SinglePlayerCommand::SinglePlayerCommand()
	:Command()
{
}

void dae::SinglePlayerCommand::Execute()
{
	rvn::GameMode::GetInstance().SinglePlayer();
}

dae::MultiPlayerCommand::MultiPlayerCommand()
	:Command()
{
}

void dae::MultiPlayerCommand::Execute()
{
	rvn::GameMode::GetInstance().MultiPlayer();
}

dae::VSPlayerCommand::VSPlayerCommand()
	:Command()
{
}

void dae::VSPlayerCommand::Execute()
{
	rvn::GameMode::GetInstance().VSPlayer();
}
