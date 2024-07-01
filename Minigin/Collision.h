#pragma once
#include "Component.h"
#include <functional>


namespace dae
{
    class Collision : public Component
    {
	public:
		Collision(GameObject* owner);
		~Collision();
		Collision(const Collision& other) = delete;
		Collision(Collision&& other) = delete;
		Collision& operator=(const Collision& other) = delete;
		Collision& operator=(Collision&& other) = delete;

		void SetScene(const std::string& sceneName);
		std::string GetLayer() const { return m_Layer; };
		void SetLayer(const std::string& layer) { m_Layer = layer; };

		void SetBounds(const float with, const float height) { m_With = with; m_Height = height; };

		void SetCallback(std::function<void(const Collision* owner, const Collision* other)> callbackFunc)
		{
			m_OnHitCallback = callbackFunc;
		}

		virtual void FixedUpdate() override;
		virtual void Render() const override;
		GameObject* GetParentGameObject() const;

	private:

		bool CheckOverlap(Collision* other);

		float m_With{ 0 };
		float m_Height{ 0 };

		std::string m_Layer{ "default" };
		std::string m_Scene{ "" };
		std::function<void(const Collision* owner, const Collision* other)> m_OnHitCallback{};

    };
}

