#pragma once
#include "Component.h"
#include <glm/glm.hpp>

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
	private:
		std::vector<glm::vec3> m_Grid{};

	};
}

