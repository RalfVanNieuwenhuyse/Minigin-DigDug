#pragma once
#include "Component.h"

namespace dae
{
	class Image;
	class Transform;
	class ImageRender : public Component
	{
	public:
		ImageRender(GameObject* owner);
		virtual ~ImageRender() = default;
		ImageRender(const ImageRender& other) = delete;
		ImageRender(ImageRender&& other) = delete;
		ImageRender& operator=(const ImageRender& other) = delete;
		ImageRender& operator=(ImageRender&& other) = delete;

		void Render() const override;

		void SetActive(bool active) { m_IsActive = active; };

		

	private:
		void CheckRequiredComponents() const;
		void SetupRequiredComponents();

		std::shared_ptr <Image> m_Image{};
		std::shared_ptr<Transform> m_Transform;

		bool m_IsActive{ true };
	};
}

