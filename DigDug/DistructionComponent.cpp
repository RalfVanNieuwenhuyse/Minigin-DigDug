#include "DistructionComponent.h"
#include "GTime.h"
#include "GameObject.h"
#include "Transform.h"

rvn::DistructionComponent::DistructionComponent(dae::GameObject* owner)
	:Component(owner)
{
}

void rvn::DistructionComponent::Update()
{
	m_Timer += dae::GTime::GetInstance().GetDeltaTime();

	if (m_Timer >= m_MaxTimer)
	{
		//GetOwner()->Destroy();
		GetOwner()->GetTransform()->SetPosition(glm::vec3{-20,-20,-20});
	}
}
