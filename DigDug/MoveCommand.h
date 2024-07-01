#pragma once
#include "Command.h"
#include <glm/glm.hpp>
#include "GridMovement.h"


class dae::Transform;

namespace rvn
{
	//class GridMovement;

	class MoveCommand final : public dae::GameObjectCommand
	{
	public:
		MoveCommand(dae::GameObject* gameObject);

		void Execute() override;
		void SetDirection(glm::vec3 direction);
		void SetMoveSpeed(float moveSpeed);

	private:
		std::shared_ptr<dae::Transform> m_Transform{ nullptr };
		std::shared_ptr<GridMovement> m_GridMovement{ nullptr };

		glm::vec3 m_Direction{};
		float m_MoveSpeed{};
	};
}

