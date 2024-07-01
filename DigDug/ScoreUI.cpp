#include "ScoreUI.h"
#include "EventManager.h"
#include "GameObject.h"
#include "PlayerScore.h"
#include "Text.h"

#include <string>

dae::ScoreUI::ScoreUI(GameObject* owner)
	:Component(owner)
{
	m_Text = GetOwner()->GetComponent<Text>();

	if (!m_Text)
	{
		throw std::invalid_argument("ScoreUI needs Text");
	}

	auto boundUpdateScore = std::bind(&ScoreUI::UpdateScore, this, std::placeholders::_1);
	GameObjectEvent event;
	event.eventType = "ScoreUpdated";
	EventManager::GetInstance().AddObserver(event, boundUpdateScore);
}

void dae::ScoreUI::UpdateScore(const dae::Event* e)
{
	if (const GameObjectEvent* GameEvent = dynamic_cast<const GameObjectEvent*>(e))
	{
		if (m_Object == GameEvent->gameObject)
		{
			m_Text->SetText("Score: " + std::to_string(GameEvent->gameObject->GetComponent<PlayerScore>()->GetScore()));
		}
	}
}
