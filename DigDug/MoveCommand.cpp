#include "MoveCommand.h"
#include "Transform.h"
#include "GTime.h"



rvn::MoveCommand::MoveCommand(dae::GameObject* gameObject)
	:GameObjectCommand(gameObject)
{
	m_Transform = GetGameObject()->GetTransform();
	m_GridMovement = GetGameObject()->GetComponent<rvn::GridMovement>();
	m_DigDugComp = GetGameObject()->GetComponent<rvn::DigDug>();
	
}

void rvn::MoveCommand::Execute()
{	
	if (!m_FirtExicute)
	{
		m_FirtExicute = true;
		m_DigDugComp = GetGameObject()->GetComponent<rvn::DigDug>();
	}
	m_GridMovement->ChangeDirection(m_Direction);
	m_GridMovement->Move();
	m_DigDugComp->SetLastDirection(m_Direction);

}

void rvn::MoveCommand::SetDirection(glm::vec3 direction)
{
	 m_Direction = direction;	 
}

