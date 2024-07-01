#include "GridComponent.h"

rvn::GridComponent::GridComponent(dae::GameObject* owner)
	:Component(owner)
{
}

const std::vector<glm::vec3>& rvn::GridComponent::CreateGrid(int rows, int collums, float cellSize, glm::vec3 offset)
{
    m_Grid.clear();
    for (int row = 0; row < rows; ++row) 
    {
        for (int col = 0; col < collums; ++col)
        {            
            float x = col * cellSize + offset.x;
            float y = row * cellSize + offset.y ;
            
            m_Grid.emplace_back(x, y, offset.z);
        }
    }

    return m_Grid;
}


