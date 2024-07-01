#pragma once
#include "GameObject.h"
namespace dae
{
	class Component
	{
	public:
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;


		virtual void Render() const {};
		virtual void Update() {};
		virtual void FixedUpdate() {};

		virtual void RenderImGui() {};
	protected:

		explicit Component(GameObject* owner);
		GameObject* GetOwner() const;

	private:
		GameObject* m_Owner{};		
	};
}