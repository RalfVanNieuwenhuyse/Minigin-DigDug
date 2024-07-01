#include "LivesComponent.h"
#include "EventManager.h"
#include "ServiceLocator.h"

dae::LivesComponent::LivesComponent(GameObject* owner)
	:Component(owner)
{
}

void dae::LivesComponent::SetLives(unsigned int nrOfLives)
{
	m_Lives = nrOfLives;

	std::unique_ptr<GameObjectEvent> event = std::make_unique<GameObjectEvent>();
	event->eventType = "LiveUpdated";
	event->gameObject = GetOwner();
	EventManager::GetInstance().SendEventMessage(std::move(event));
}

void dae::LivesComponent::RemoveLives(const unsigned int nrOfLives)
{
	unsigned int minuslives = nrOfLives;
	if (minuslives > m_Lives)
	{
		minuslives = m_Lives;
	}
	m_Lives -= minuslives;


	servicelocator::get_sound_system().Play(SoundData{ 0, 1/*, dae::SoundData::SoundType::SoundEffect, "pacman_death.wav" ,true*/ });

	std::unique_ptr<GameObjectEvent> event = std::make_unique<GameObjectEvent>();
	event->eventType = "LiveUpdated";
	event->gameObject = GetOwner();
	EventManager::GetInstance().SendEventMessage(std::move(event));
}

unsigned int dae::LivesComponent::GetLives()
{
	return m_Lives;
}
