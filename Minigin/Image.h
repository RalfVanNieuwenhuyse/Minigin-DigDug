#pragma once
#include <memory>
#include <string>
#include "Component.h"
#include "glm/glm.hpp"

namespace dae 
{
    class Texture2D;
    class Image : public Component
    {
	public:
		Image(GameObject* owner);
		virtual ~Image() = default;
		Image(const Image& other) = delete;
		Image(Image&& other) = delete;
		Image& operator=(const Image& other) = delete;
		Image& operator=(Image&& other) = delete;

		void SetTexture(const std::string& filename);
		void SetTexture(std::shared_ptr<Texture2D>& texture);

		glm::vec2 GetTextureDimensions() const;
		float GetTextureWidth() const;
		float GetTextureHeight() const;

		
		std::shared_ptr<Texture2D> GetTexture() const;

	private:
		std::shared_ptr<Texture2D> m_Texture{ nullptr };
    };
}

