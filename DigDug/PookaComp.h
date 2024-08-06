#pragma once

#include "Component.h"
#include "PookaStates.h"
#include "Event.h"

namespace rvn
{
	class PookaComp : public dae::Component
	{
	public:
		PookaComp(dae::GameObject* owner);
		~PookaComp() = default;
		PookaComp(const PookaComp& other) = delete;
		PookaComp(PookaComp&& other) = delete;
		PookaComp& operator=(const PookaComp& other) = delete;
		PookaComp& operator=(PookaComp&& other) = delete;

		void Update() override;
		void SetState(EPookaState state);
		dae::GameObject* GetGameObjectOwner() const;


	private:

		std::unique_ptr<PookaStates> m_currentState;
	};
}