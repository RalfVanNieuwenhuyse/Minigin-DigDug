#pragma once
#include "Command.h"
#include <glm/glm.hpp>
#include "GridMovement.h"
#include "DigDug.h"
#include "FygarComp.h"

class dae::Transform;

namespace rvn
{
	//class GridMovement;
	//class DigDug;

	class MoveCommand final : public dae::GameObjectCommand
	{
	public:
		MoveCommand(dae::GameObject* gameObject);

		void Execute() override;
		void SetDirection(glm::vec3 direction);

	private:
		std::shared_ptr<dae::Transform> m_Transform{ nullptr };
		std::shared_ptr<GridMovement> m_GridMovement{ nullptr };
		std::shared_ptr<DigDug> m_DigDugComp{ nullptr };

		glm::vec3 m_Direction{};

		bool m_FirtExicute{false};
	};

	class MoveCommandF final : public dae::GameObjectCommand
	{
	public:
		MoveCommandF(dae::GameObject* gameObject);

		void Execute() override;
		void SetDirection(glm::vec3 direction);

	private:
		std::shared_ptr<dae::Transform> m_Transform{ nullptr };
		std::shared_ptr<GridMovement> m_GridMovement{ nullptr };
		std::shared_ptr<FygarComp> m_FygarComp{ nullptr };

		glm::vec3 m_Direction{};

		bool m_FirtExicute{ false };
	};
}

