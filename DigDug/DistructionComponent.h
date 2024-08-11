#pragma once
#include "Component.h"
namespace rvn
{
	class DistructionComponent : public dae::Component
	{
	public:
		DistructionComponent(dae::GameObject* owner);
		~DistructionComponent() = default;
		DistructionComponent(const DistructionComponent& other) = delete;
		DistructionComponent(DistructionComponent&& other) = delete;
		DistructionComponent& operator=(const DistructionComponent& other) = delete;
		DistructionComponent& operator=(DistructionComponent&& other) = delete;

		void Update() override;
		void SetLifeTime(float lifetime) { m_MaxTimer = lifetime; };

	private:
		float m_Timer{};
		float m_MaxTimer{};
	};
}

