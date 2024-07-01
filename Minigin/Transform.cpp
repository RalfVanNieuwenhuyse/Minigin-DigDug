#include "GameObject.h"
#include "Transform.h"

dae::Transform::Transform(GameObject* owner)
	: Component(owner)
{
	m_Position.x = 0.f;
	m_Position.y = 0.f;
	m_Position.z = 0.f;
	SetPositionDirty();
}

const glm::vec3& dae::Transform::GetPosition()
{
	if (m_PositionIsDirty)
		UpdateWorldPosition();
	return m_Position;
}

const glm::vec3& dae::Transform::GetLocalPosition()
{
	return m_LocalPosition;
}

void dae::Transform::SetPosition(const float x, const float y, const float z)
{
	m_LocalPosition.x = x;
	m_LocalPosition.y = y;
	m_LocalPosition.z = z;
	SetPositionDirty();
}

void dae::Transform::SetPosition(const glm::vec3& newPos)
{
	m_LocalPosition = newPos;
	SetPositionDirty();
}

void dae::Transform::SetPositionDirty()
{
	m_PositionIsDirty = true;
	for (auto& child : GetOwner()->GetChildren())
	{
		child->GetTransform()->SetPositionDirty();
	}
}

void dae::Transform::UpdateWorldPosition()
{
	const auto Owner = GetOwner();
	if (!Owner->GetParent())
	{
		m_Position = m_LocalPosition;
	}
	else
	{
		const auto parentTransform = Owner->GetParent()->GetTransform();
		m_Position = parentTransform.get()->GetPosition() + m_LocalPosition;
	}
	m_PositionIsDirty = false;
}
