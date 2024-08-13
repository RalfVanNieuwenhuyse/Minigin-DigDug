#include "PlayerScore.h"
#include "EventManager.h"

dae::PlayerScore::PlayerScore(GameObject* owner)
	:Component(owner)
{
}

void dae::PlayerScore::SetScore(const unsigned int score)
{
	m_Score = score;

    std::shared_ptr<GameObjectEvent> event = std::make_shared<GameObjectEvent>();
    event->eventType = "ScoreUpdated";
    event->gameObject = GetOwner();
    EventManager::GetInstance().SendEventMessage(std::move(event));
}

void dae::PlayerScore::AddScore(const unsigned int score)
{
    if (score > UINT_MAX - m_Score)
    {
        m_Score = UINT_MAX;
    }
    else 
    {
        m_Score += score;
    }

    std::shared_ptr<GameObjectEvent> event = std::make_shared<GameObjectEvent>();
    event->eventType = "ScoreUpdated";
    event->gameObject = GetOwner();
    EventManager::GetInstance().SendEventMessage(std::move(event));
}

unsigned int dae::PlayerScore::GetScore()
{
	return m_Score;
}
