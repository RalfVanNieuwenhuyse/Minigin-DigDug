#pragma once
#include "Component.h"
#include "Event.h"
#include <glm/glm.hpp>
#include "FygarState.h"

namespace rvn
{

	class FygarComp : public dae::Component
	{
	public:
		FygarComp(dae::GameObject* owner);
		~FygarComp() = default;
		FygarComp(const FygarComp& other) = delete;
		FygarComp(FygarComp&& other) = delete;
		FygarComp& operator=(const FygarComp& other) = delete;
		FygarComp& operator=(FygarComp&& other) = delete;

		void Update() override;
		void SetState(EFygarState state);
		dae::GameObject* GetGameObjectOwner() const;


	private:

		std::unique_ptr<FygarState> m_currentState;

		glm::vec3 m_FirstPos{};
		bool m_IsFirtsFrame{ true };
		void ResetLevel(const dae::Event* e);
	};
}
