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

		void SetIsPlayer2(bool isPlayer2) { m_IsMultyPlaye02 = isPlayer2; };
		bool IsPlayer2() { return m_IsMultyPlaye02; };

		void SetLastDirection(const glm::vec3& direction) { m_LastDirection = direction; };
		const glm::vec3& GetLastDirection() { return m_LastDirection; };

		void Exicute();

	private:

		std::unique_ptr<FygarState> m_currentState;

		glm::vec3 m_FirstPos{};
		bool m_IsFirtsFrame{ true };
		void ResetLevel(const dae::Event* e);

		bool m_IsMultyPlaye02{ false };

		glm::vec3 m_LastDirection{};
	};
}
