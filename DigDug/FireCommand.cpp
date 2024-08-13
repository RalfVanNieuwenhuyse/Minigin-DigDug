#include "FireCommand.h"

rvn::FireCommand::FireCommand(dae::GameObject* gameObject)
	:GameObjectCommand(gameObject)
{
	m_FygarComp = GetGameObject()->GetComponent<rvn::FygarComp>();

}

void rvn::FireCommand::Execute()
{
	if (!m_FirtExicute)
	{
		m_FirtExicute = true;
		m_FygarComp = GetGameObject()->GetComponent<rvn::FygarComp>();
	}

	m_FygarComp->Exicute();
}
