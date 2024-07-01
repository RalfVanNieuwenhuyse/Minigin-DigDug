#pragma once
#include "Component.h"
#include "Event.h"

namespace dae
{
	class Text;

	class LivesUI :	public Component
	{
	public:
		LivesUI(GameObject* owner);
		~LivesUI() = default;
		LivesUI(const LivesUI& other) = delete;
		LivesUI(LivesUI&& other) = delete;
		LivesUI& operator=(const LivesUI& other) = delete;
		LivesUI& operator=(LivesUI&& other) = delete;

		void SetObjectToCheck(GameObject* object) { m_Object = object; };

	private:
		void UpdateLives(const dae::Event* e);

		std::shared_ptr<Text> m_Text;
		GameObject* m_Object{nullptr};
	};
}


