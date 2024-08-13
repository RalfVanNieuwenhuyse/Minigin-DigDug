#include "PumpCommand.h"
#include "EventManager.h"
#include "Event.h"

rvn::PumpCommand::PumpCommand(dae::GameObject* gameObject)
	:dae::GameObjectCommand(gameObject)
{
}

void rvn::PumpCommand::Execute()
{
    std::shared_ptr<dae::GameObjectEvent> event = std::make_shared<dae::GameObjectEvent>();
    event->eventType = "PumpCommand";
    event->gameObject = GetGameObject();
    dae::EventManager::GetInstance().SendEventMessage(std::move(event));
}

