#include <stdexcept>

#include "ImageRender.h"
#include "Renderer.h"
#include "Image.h"
#include "Transform.h"


dae::ImageRender::ImageRender(GameObject* owner)
	:Component(owner)
{
	SetupRequiredComponents();
	CheckRequiredComponents();	
}

void dae::ImageRender::Render() const
{
	if (!m_IsActive) return;
	const auto& pos = m_Transform->GetPosition();
	Renderer::GetInstance().RenderTexture(*m_Image->GetTexture(), pos.x, pos.y);
}

void dae::ImageRender::CheckRequiredComponents() const
{
	if (!m_Image)
	{
		throw std::invalid_argument("ImageRenderComponent needs a ImageComponent");
	}
	if (!m_Transform)
	{
		throw std::invalid_argument("ImageRenderComponent needs a TransformComponent");
	}
}

void dae::ImageRender::SetupRequiredComponents()
{
	auto owner = GetOwner();
	if (!m_Image)
	{
		m_Image = owner->GetComponent<Image>();

		if (!m_Image)
		{
			m_Image = owner->AddComponent<Image>();
		}
	}
	m_Transform = owner->GetTransform();
}
