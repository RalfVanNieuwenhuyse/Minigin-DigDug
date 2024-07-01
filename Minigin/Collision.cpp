#include "Collision.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Transform.h"
#include <iostream>
#include <execution>
#include <algorithm>

dae::Collision::Collision(GameObject* owner)
	:Component(owner)
{
	
}

dae::Collision::~Collision()
{
	dae::SceneManager::GetInstance().GetScene(m_Scene)->RemoveCollision(this);
}

void dae::Collision::SetScene(const std::string& sceneName)
{
	auto scene = dae::SceneManager::GetInstance().GetScene(sceneName);
	m_Scene = sceneName;
	if (scene != nullptr)
	{
		scene->AddCollision(this);
	}
}

void dae::Collision::FixedUpdate()
{
	auto collisionOwner = GetOwner();
	const auto& collisions = dae::SceneManager::GetInstance().GetActiveScene().GetCollisions();
	
	if (!m_OnHitCallback)
		return;

	

	std::for_each(std::execution::par_unseq, collisions.begin(), collisions.end(), [&](const auto& collisionToCheck) {
		if (collisionOwner == collisionToCheck->GetOwner())
			return;

		if (!CheckOverlap(collisionToCheck))
			return;

		m_OnHitCallback(this, collisionToCheck);
		});
}

void dae::Collision::Render() const
{
}

dae::GameObject* dae::Collision::GetParentGameObject() const
{
	return GetOwner();
}

bool dae::Collision::CheckOverlap(Collision* other)
{
	const auto worldPos = GetOwner()->GetTransform()->GetPosition();
	const auto otherWorldPos = other->GetOwner()->GetTransform()->GetPosition();

	const float left = worldPos.x;
	const float right = worldPos.x + m_With;
	const float top = worldPos.y;
	const float bottom = worldPos.y + m_Height;

	const float otherLeft = otherWorldPos.x;
	const float otherRight = otherWorldPos.x + other->m_With;
	const float otherTop = otherWorldPos.y;
	const float otherBottom = otherWorldPos.y + other->m_Height;

	// Early exit if bounding boxes don't overlap
	if (right < otherLeft || left > otherRight || bottom < otherTop || top > otherBottom)
		return false;

	// Bounding boxes overlap, so there is potential intersection
	return true;
}
