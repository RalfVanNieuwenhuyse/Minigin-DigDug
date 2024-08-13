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

		void SetLastDirection(const glm::vec3& direction) { m_LastDirection = direction; };
		const glm::vec3& GetLastDirection() {return m_LastDirection;};

		const std::vector<dae::GameObject*>& GetPumps() { return m_Pumps; };

		void SetIsPlayer2(bool isPlayer2) { m_IsMultyPlaye02 = isPlayer2; };
		bool IsPlayer2() { return m_IsMultyPlaye02; };

	private:

		std::unique_ptr<PlayerStates> m_currentState;
		glm::vec3 m_FirstPos{};
		bool m_IsFirtsFrame{true};
		void ResetLevel(const dae::Event* e);

		std::vector<dae::GameObject*> m_Pumps;

		bool m_IsMultyPlaye02{false};

		glm::vec3 m_LastDirection{};
	};
}

