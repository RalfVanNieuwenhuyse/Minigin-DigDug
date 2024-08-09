#pragma once
#include "Component.h"
#include "PlayerStates.h"
#include "Event.h"
#include <glm/glm.hpp>


namespace rvn
{
	class DigDug : public dae::Component
	{
	public:
		DigDug(dae::GameObject* owner);
		~DigDug() = default;
		DigDug(const DigDug& other) = delete;
		DigDug(DigDug&& other) = delete;
		DigDug& operator=(const DigDug& other) = delete;
		DigDug& operator=(DigDug&& other) = delete;
		
		void Update() override;
		void SetState(PlayerState state);
		dae::GameObject* GetGameObjectOwner() const;

		

	private:

		std::unique_ptr<PlayerStates> m_currentState;
		glm::vec3 m_FirstPos{};
		bool m_IsFirtsFrame{true};
		void ResetLevel(const dae::Event* e);
	};
}

