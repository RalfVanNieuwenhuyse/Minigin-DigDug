#pragma once
#include "Component.h"
#include <memory>
#include "Transform.h"
#include "Texture2D.h"
#include <string>

namespace dae
{
	class Text;
	
	class FPS : public Component
	{
	public:
		FPS(GameObject* owner);
		~FPS() = default;
		FPS(const FPS& other) = delete;
		FPS(FPS&& other) = delete;
		FPS& operator=(const FPS& other) = delete;
		FPS& operator=(FPS&& other) = delete;

		virtual void Update() override;

	private:
		void CheckRequiredComponents() const;
		
		std::shared_ptr<Text> m_Text;	

		const float m_MaxDelay{0.1f};
		float m_Delay{0};
		int m_Count{0};

		bool m_SkipFirstFrame{ true };
	};
}

