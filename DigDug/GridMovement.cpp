#include "GridMovement.h"
#include "Transform.h"
#include "GTime.h"
#include <iostream>

#include <algorithm> // for std::min_element
#include <glm/gtx/norm.hpp> // for glm::distance2

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
        float m_InterpolationFactor = 0.1f;
        auto currentPosition = GetOwner()->GetComponent<dae::Transform>()->GetPosition();
        auto closestPoint = GetClosestGridPoint(currentPosition);

        // Determine whether to move along the x-axis or y-axis based on the direction
        if (glm::abs(m_Direction.x) > glm::abs(m_Direction.y))
        {
            // Move along the x-axis
            float directionSign = (m_Direction.x > 0) ? 1.0f : -1.0f;
            currentPosition.x += directionSign * m_Speed * dae::GTime::GetInstance().GetDeltaTime();

            // Interpolate y position towards closest grid point
            currentPosition.y += (closestPoint.y - currentPosition.y) * m_InterpolationFactor;
        }
        else
        {
            // Move along the y-axis
            float directionSign = (m_Direction.y > 0) ? 1.0f : -1.0f;
            currentPosition.y += directionSign * m_Speed * dae::GTime::GetInstance().GetDeltaTime();

            // Interpolate x position towards closest grid point
            currentPosition.x += (closestPoint.x - currentPosition.x) * m_InterpolationFactor;
        }

        // Update the position
        GetOwner()->GetComponent<dae::Transform>()->SetPosition(currentPosition);
    }
}

void rvn::GridMovement::ChangeDirection(const glm::vec3& direction)
{	
	m_Direction = direction;
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