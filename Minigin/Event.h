#pragma once
#include <string>
#include "Component.h"

namespace dae
{
	struct Event
	{
		virtual ~Event() = default;
		const char* eventType{};
	};

	struct ComponentEvent : Event
	{
		Component* component;
	};

	struct GameObjectEvent : Event
	{
		GameObject* gameObject;
	};

	inline bool operator==(const Event& lhs, const Event& rhs)
	{
		return lhs.eventType == rhs.eventType;
	}
}

template<>
struct std::hash<dae::Event>
{
	std::size_t operator()(const dae::Event& input) const
	{
		return std::hash<const char*>{}(input.eventType);
	}
};