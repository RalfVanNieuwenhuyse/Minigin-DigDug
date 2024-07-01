#include "MoveCommand.h"
#include "Transform.h"
#include "GTime.h"

rvn::MoveCommand::MoveCommand(dae::GameObject* gameObject)
	:GameObjectCommand(gameObject)
{
	m_Transform = GetGameObject()->GetTransform();
	m_GridMovement = GetGameObject()->GetComponent<rvn::GridMovement>();
}

void rvn::MoveCommand::Execute()
{	
	m_GridMovement->ChangeDirection(m_Direction);
	m_GridMovement->Move();
}

void rvn::MoveCommand::SetDirection(glm::vec3 direction)
{
	 m_Direction = direction;	 
}

void rvn::MoveCommand::SetMoveSpeed(float moveSpeed)
{
	m_MoveSpeed = moveSpeed;
}
