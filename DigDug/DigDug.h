#pragma once
#include "Component.h"
#include "PlayerStates.h"
#include "Event.h"

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

		void ChangeState(const dae::Event* e);

	private:

		std::unique_ptr<PlayerStates> m_currentState;


	};
}

