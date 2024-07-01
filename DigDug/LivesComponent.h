#pragma once
#include "Component.h"

namespace dae
{
	class LivesComponent :  public Component
	{
	public:
		LivesComponent(GameObject* owner);
		~LivesComponent() = default;
		LivesComponent(const LivesComponent& other) = delete;
		LivesComponent(LivesComponent&& other) = delete;
		LivesComponent& operator=(const LivesComponent& other) = delete;
		LivesComponent& operator=(LivesComponent&& other) = delete;

		void SetLives(const unsigned int nrOfLives);
		void RemoveLives(const unsigned int nrOfLives = 1);

		unsigned int GetLives();

	private:

		unsigned int m_Lives{3};

	};
}


