#include "MoveCommand.h"
#include "Transform.h"
#include "GTime.h"


rvn::MoveCommand::MoveCommand(dae::GameObject* gameObject)
	:GameObjectCommand(gameObject)
{
	m_Transform = GetGameObject()->GetTransform();

}

void rvn::MoveCommand::Execute()
{	
	/*auto newPos = m_Transform->GetLocalPosition() + m_Direction * m_MoveSpeed * dae::GTime::GetInstance().GetDeltaTime();
	m_Transform->SetPosition(newPos);*/
}

void rvn::MoveCommand::SetDirection(glm::vec3 direction)
{
	 m_Direction = direction;	 
}

void rvn::MoveCommand::SetMoveSpeed(float moveSpeed)
{
	m_MoveSpeed = moveSpeed;
}
