#include "GridMovement.h"
#include "Transform.h"
#include "GTime.h"
#include <iostream>

#include <algorithm> // for std::min_element
#pragma warning(disable : 4201)
#include <glm/gtx/norm.hpp>
#pragma warning(default : 4201)


rvn::GridMovement::GridMovement(dae::GameObject* owner)
	:Component(owner)
{
}

void rvn::GridMovement::Update()
{
	
}

void rvn::GridMovement::Move()
{
    if (glm::length2(m_Direction) > 0)
    {
        auto currentPosition = GetOwner()->GetTransform()->GetPosition();
        auto newPosition = currentPosition;
        auto closestPoint = GetClosestGridPoint(currentPosition);

        float snapTreshHold = 5.f;                
       
        if (glm::abs(m_Direction.x) > glm::abs(m_Direction.y))
        {
            if (glm::abs(closestPoint.y - currentPosition.y) < snapTreshHold)
            {               
                float directionSign = (m_Direction.x > 0) ? 1.0f : -1.0f;
                newPosition.x += directionSign * m_Speed * dae::GTime::GetInstance().GetDeltaTime();
                newPosition.y += (closestPoint.y - newPosition.y) * m_InterpolationFactor;
                m_PreviousDirection = m_Direction;
            }
            else
            {
                m_Direction = m_PreviousDirection;
                float directionSign = (m_PreviousDirection.y > 0) ? 1.0f : -1.0f;
                newPosition.y += directionSign * m_Speed * dae::GTime::GetInstance().GetDeltaTime();
                newPosition.x += (closestPoint.x - newPosition.x) * m_InterpolationFactor;
            }

        }
        else
        {
            if (glm::abs(closestPoint.x - currentPosition.x) < snapTreshHold)
            {
                float directionSign = (m_Direction.y > 0) ? 1.0f : -1.0f;
                newPosition.y += directionSign * m_Speed * dae::GTime::GetInstance().GetDeltaTime();
                newPosition.x += (closestPoint.x - newPosition.x) * m_InterpolationFactor;
                m_PreviousDirection = m_Direction;

            } 
            else
            {
                m_Direction = m_PreviousDirection;
                float directionSign = (m_PreviousDirection.x > 0) ? 1.0f : -1.0f;
                newPosition.x += directionSign * m_Speed * dae::GTime::GetInstance().GetDeltaTime();
                newPosition.y += (closestPoint.y - newPosition.y) * m_InterpolationFactor;
            }
        }

        if (IsWithinGridBounds(newPosition))
        {
            currentPosition = newPosition;
        }
        GetOwner()->GetTransform()->SetPosition(currentPosition);        
    }
}

void rvn::GridMovement::ChangeDirection(const glm::vec3& direction)
{	
	m_Direction = direction;
}

void rvn::GridMovement::SetGrid(std::vector<glm::vec3> grid)
{
    m_Grid = grid;
    auto currentPosition = GetOwner()->GetTransform()->GetPosition();
    auto closestPoint = GetClosestGridPoint(currentPosition);
    GetOwner()->GetTransform()->SetPosition(glm::vec3{ closestPoint.x,closestPoint.y,currentPosition.z });
}

glm::vec3 rvn::GridMovement::GetClosestGridPoint(const glm::vec3& position)
{
    auto closestPoint = *std::min_element(m_Grid.begin(), m_Grid.end(),
        [&](const glm::vec3& a, const glm::vec3& b)
        {
        	return glm::distance2(position, a) < glm::distance2(position, b);
        });

	return closestPoint;
}

bool rvn::GridMovement::IsWithinGridBounds(const glm::vec3& position)
{
    // Find the minimum and maximum bounds of the grid
    float minX = std::min_element(m_Grid.begin(), m_Grid.end(), [](const glm::vec3& a, const glm::vec3& b) { return a.x < b.x; })->x;
    float maxX = std::max_element(m_Grid.begin(), m_Grid.end(), [](const glm::vec3& a, const glm::vec3& b) { return a.x < b.x; })->x;
    float minY = std::min_element(m_Grid.begin(), m_Grid.end(), [](const glm::vec3& a, const glm::vec3& b) { return a.y < b.y; })->y;
    float maxY = std::max_element(m_Grid.begin(), m_Grid.end(), [](const glm::vec3& a, const glm::vec3& b) { return a.y < b.y; })->y;

    return position.x >= minX && position.x <= maxX && position.y >= minY && position.y <= maxY;
}