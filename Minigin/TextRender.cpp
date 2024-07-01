#include <stdexcept>
#include "TextRender.h"
#include "Renderer.h"
#include "Text.h"
#include "Transform.h"

dae::TextRender::TextRender(GameObject* owner)
	:Component(owner)
{
	SetupRequiredComponents();
	CheckRequiredComponents();
}

void dae::TextRender::Render() const
{
	if (!m_IsActive) return;
	const auto& pos = m_Transform->GetPosition();
	Renderer::GetInstance().RenderTexture(*m_Text->GetTexture(), pos.x, pos.y);
}

void dae::TextRender::CheckRequiredComponents() const
{
	if (!m_Text)
	{
		throw std::invalid_argument("TextRender needs Text");
	}
	if (!m_Transform)
	{
		throw std::invalid_argument("ImageRender needs a Transform");
	}
}

void dae::TextRender::SetupRequiredComponents()
{
	auto Owner = GetOwner();
	if (!m_Text)
	{
		m_Text = Owner->GetComponent<Text>();
		if (!m_Text)
		{
			m_Text = Owner->AddComponent<Text>();
		}
	}
	m_Transform = Owner->GetTransform();
}
