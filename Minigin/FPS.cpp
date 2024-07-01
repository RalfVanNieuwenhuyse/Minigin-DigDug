#include "FPS.h"
#include "Text.h"
#include "GTime.h"

dae::FPS::FPS(GameObject* owner)
	:Component(owner)
{	
	m_Text = GetOwner()->GetComponent<Text>();
	CheckRequiredComponents();
}

void dae::FPS::Update()
{
	m_Delay += dae::GTime::GetInstance().GetDeltaTime();
	m_Count++;
	if (m_Delay >= m_MaxDelay )
	{
		m_Text->SetText(std::format("{:.1f}", m_Count / m_Delay));
		m_Delay = 0;
		m_Count = 0;
	}	
}

void dae::FPS::CheckRequiredComponents() const
{
	if (!m_Text)
	{
		throw std::invalid_argument("FPS needs Text");
	}
}