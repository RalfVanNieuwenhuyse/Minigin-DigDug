#pragma once
#include <numbers>
#include <glm/glm.hpp>
#include "Component.h"

namespace dae
{
	class Transform;
	class Rotatetor final : public Component
	{
	public:
		Rotatetor(GameObject* owner);

		~Rotatetor() = default;
		Rotatetor(const Rotatetor& other) = delete;
		Rotatetor(Rotatetor&& other) = delete;
		Rotatetor& operator=(const Rotatetor& other) = delete;
		Rotatetor& operator=(Rotatetor&& other) = delete;

		void Update() override;

		void SetRotateSpeed(float speed);
		void SetCircleRadius(float radius);

	private:
		void CheckForRequiredComponents() const;
		void SetupRequiredComponents();
		std::shared_ptr<Transform> m_Transform{};

		float m_RotateSpeed{ 2 };
		float m_CircleRadius{ 20 };

		float m_LastCircleProgress{ 0 };
		const float MAX_ROTATION{ static_cast<float>(2.0f * std::numbers::pi) };
		

	};
}