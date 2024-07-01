#include "Image.h"
#include "ResourceManager.h"
#include "Texture2D.h"


dae::Image::Image(GameObject* owner)
	:Component(owner)
{
}

void dae::Image::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::Image::SetTexture(std::shared_ptr<Texture2D>& texture)
{
	m_Texture = texture;
}

glm::vec2 dae::Image::GetTextureDimensions() const
{
	return static_cast<glm::vec2>(m_Texture->GetSize());
}

float dae::Image::GetTextureWidth() const
{
	return static_cast<float>(m_Texture->GetSize().x);
}

float dae::Image::GetTextureHeight() const
{
	return static_cast<float>(m_Texture->GetSize().y);
}

std::shared_ptr<dae::Texture2D> dae::Image::GetTexture() const
{
	return m_Texture;
}
