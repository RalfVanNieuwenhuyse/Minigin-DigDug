#include "GridComponent.h"
#include "Prefabs.h"
#include <iostream>


rvn::GridComponent::GridComponent(dae::GameObject* owner)
	:Component(owner)
{
}

const std::vector<glm::vec3>& rvn::GridComponent::CreateGrid(int rows, int collums, float cellSize, glm::vec3 offset)
{
    m_Grid.clear();
    m_Rows = rows;
    m_Collums = collums;
    m_Cellsize = cellSize;
    m_Offset = offset;

    for (int row = 0; row < rows; ++row) 
    {
        for (int col = 0; col < collums; ++col)
        {            
            float x = col * cellSize + offset.x;
            float y = row * cellSize + offset.y ;
            
            m_Grid.emplace_back(x, y, offset.z);
            m_HasBeenDug.emplace_back(false);
        }
    }

    return m_Grid;
}

void rvn::GridComponent::DigCell(int cellNumber, dae::Scene& scene)
{
    if (m_HasBeenDug[cellNumber]) return;
    m_HasBeenDug[cellNumber] = true;
       
    glm::vec3 newPosDug = m_Grid[cellNumber];
    newPosDug.x += -1.f;
    newPosDug.y += -1.f;
    newPosDug.z += .5f;
    rvn::Prefab::createDugSpace(scene, newPosDug);
}

int rvn::GridComponent::GetCellIndexAtPosition(glm::vec3 position) const
{
    int col = static_cast<int>((position.x - m_Offset.x) / m_Cellsize);
    int row = static_cast<int>((position.y - m_Offset.y) / m_Cellsize);

    if (col >= 0 && col < m_Collums && row >= 0 && row < m_Rows)
    {
        int cellIndex = row * m_Collums + col;
        return cellIndex;
    }

    return -1;
}

bool rvn::GridComponent::IsCellDug(glm::vec3 position)
{
    int cellindx = GetCellIndexAtPosition(position);   
    if (cellindx == -1) return false;
    return IsCellDug(cellindx);
}

void rvn::GridComponent::DigCell(glm::vec3 position, dae::Scene& scene)
{
    if (IsCellDug(position)) return;
    DigCell(GetCellIndexAtPosition(position),scene);
}

bool rvn::GridComponent::IsWithinGridBounds(const glm::vec3& position)
{
    // Find the minimum and maximum bounds of the grid
    float minX = std::min_element(m_Grid.begin(), m_Grid.end(), [](const glm::vec3& a, const glm::vec3& b) { return a.x < b.x; })->x;
    float maxX = std::max_element(m_Grid.begin(), m_Grid.end(), [](const glm::vec3& a, const glm::vec3& b) { return a.x < b.x; })->x;
    float minY = std::min_element(m_Grid.begin(), m_Grid.end(), [](const glm::vec3& a, const glm::vec3& b) { return a.y < b.y; })->y;
    float maxY = std::max_element(m_Grid.begin(), m_Grid.end(), [](const glm::vec3& a, const glm::vec3& b) { return a.y < b.y; })->y;

    return position.x >= minX && position.x <= maxX && position.y >= minY && position.y <= maxY;
}
