#pragma once
#include "GameObject.h"
namespace dae
{
	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute() = 0;
		bool Active = true;
	};

	class GameObjectCommand : public Command
	{
		GameObject* m_gameObject;
	protected:
		GameObject* GetGameObject() const { return m_gameObject; }
	public:
		explicit GameObjectCommand(GameObject* gameObject);
		virtual ~GameObjectCommand() = default;
	};
}

