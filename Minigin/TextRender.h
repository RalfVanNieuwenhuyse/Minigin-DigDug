#pragma once
#include "Component.h"

namespace dae
{
    class Text;
    class Transform;

    class TextRender : public Component
    {
	public:
		TextRender(GameObject* owner);

		~TextRender() = default;
		TextRender(const TextRender& other) = delete;
		TextRender(TextRender&& other) = delete;
		TextRender& operator=(const TextRender& other) = delete;
		TextRender& operator=(TextRender&& other) = delete;

		void Render() const override;

		void SetActive(bool isActive) { m_IsActive = isActive; };

	private:
		void CheckRequiredComponents() const;
		void SetupRequiredComponents();

		std::shared_ptr <Text> m_Text{};
		std::shared_ptr <Transform> m_Transform{};

		bool m_IsActive{ true };
    };
}

