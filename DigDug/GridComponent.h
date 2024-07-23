#pragma once
#include "Component.h"
#include <glm/glm.hpp>

#include "SceneManager.h"
#include "Scene.h"

namespace rvn
{
	class GridComponent : public dae::Component
	{
	public:
		GridComponent(dae::GameObject* owner);
		~GridComponent() = default;
		GridComponent(const GridComponent& other) = delete;
		GridComponent(GridComponent&& other) = delete;
		GridComponent& operator=(const GridComponent& other) = delete;
		GridComponent& operator=(GridComponent&& other) = delete;

		const std::vector<glm::vec3>& CreateGrid(int rows, int collums, float cellSize, glm::vec3 offset = glm::vec3{});
		const std::vector<glm::vec3>& GetGrid() const { return m_Grid; };		
		bool IsCellDug(int cellNumber) { return m_HasBeenDug[cellNumber]; };
		void DigCell(int cellNumber, dae::Scene& scene);

		int GetCellIndexAtPosition(glm::vec3 position) const;
		bool IsCellDug(glm::vec3 position);
		void DigCell(glm::vec3 position, dae::Scene& scene);

	private:
		std::vector<glm::vec3> m_Grid{};
		std::vector<bool> m_HasBeenDug{};

		int m_Rows{};
		int m_Collums{};
		float m_Cellsize{};
		glm::vec3 m_Offset{};
	};
}

