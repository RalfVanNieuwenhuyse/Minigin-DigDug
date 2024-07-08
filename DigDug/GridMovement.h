#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace rvn
{
	class GridMovement final : public dae::Component
	{
	public:
		GridMovement(dae::GameObject* owner);
		~GridMovement() = default;
		GridMovement(const GridMovement& other) = delete;
		GridMovement(GridMovement&& other) = delete;
		GridMovement& operator=(const GridMovement& other) = delete;
		GridMovement& operator=(GridMovement&& other) = delete;

		void Update() override;

		void Move();
		void SetSpeed(const float& speed) { m_Speed = speed; };
		void SetSnapTreshHold(const float& treshhold) { m_SnapTreshhold = treshhold; };
		void ChangeDirection(const glm::vec3& direction);

		void SetGrid(std::vector<glm::vec3> grid);


	private:
		float m_Speed{};
		float m_SnapTreshhold{5.f};
		float m_InterpolationFactor{0.1f};
		glm::vec3 m_Direction{};	

		glm::vec3 m_PreviousDirection{};

		std::vector<glm::vec3> m_Grid{};
		glm::vec3 GetClosestGridPoint(const glm::vec3& position);
	};
}

