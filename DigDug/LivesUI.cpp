#include "LivesUI.h"
#include "EventManager.h"
#include "GameObject.h"
#include "LivesComponent.h"
#include "Text.h"

#include <string>

dae::LivesUI::LivesUI(GameObject* owner)
	:Component(owner)
{
	m_Text = GetOwner()->GetComponent<Text>();

	if (!m_Text)
	{
		throw std::invalid_argument("LivesUI needs Text");
	}

	auto boundUpdateLife = std::bind(&LivesUI::UpdateLives, this, std::placeholders::_1);
	GameObjectEvent event;
	event.eventType = "LiveUpdated";
	EventManager::GetInstance().AddObserver(event, boundUpdateLife);
}

void dae::LivesUI::UpdateLives(const dae::Event* e)
{
	if (const GameObjectEvent* GameEvent = dynamic_cast<const GameObjectEvent*>(e))
	{
		if (m_Object == GameEvent->gameObject)
		{
			m_Text->SetText("Lives: " + std::to_string(GameEvent->gameObject->GetComponent<LivesComponent>()->GetLives()));
		}		
	}	
}
