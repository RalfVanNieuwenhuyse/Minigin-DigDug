#pragma once
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>
//#include "Component.h"

namespace dae
{
	//class Texture2D;
	class Component;
	class Transform;	

	class GameObject final : public std::enable_shared_from_this<GameObject>
	{
	public:		
		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update();
		void FixedUpdate();
		void Render() const;
		void RenderImGui() const;

		void Destroy();
		bool IsDestroyed();

		template <typename T> std::shared_ptr <T> AddComponent();
		template <typename T> std::shared_ptr <T> GetComponent();
		template <typename T> void RemoveComponent();

		std::shared_ptr<dae::Transform> GetTransform() const;

		void SetParent(GameObject* parent, bool keepWorldPosition);		
		const GameObject* GetParent() const;

		void ClearChildren();
		std::vector<std::shared_ptr<GameObject>> GetChildren() const;

		void SetActive(bool state) { m_Active = state; };
		bool GetActive() { return m_Active; };
		
	private:

		void RemoveChild(const std::shared_ptr<GameObject>& child);
		void AddChild(const std::shared_ptr<GameObject>& child);

		GameObject* m_Parent{ nullptr };

		std::vector<std::shared_ptr<GameObject>> m_Children;

		std::shared_ptr<Transform> m_transform{};
		std::vector<std::shared_ptr<Component>> m_Components{};

		bool m_IsDestroyed = false;
		bool m_Active{true};
	};

	template<typename T>
	inline std::shared_ptr <T> dae::GameObject::AddComponent()
	{
		std::shared_ptr <T> foundComponent = GetComponent<T>();
		if (foundComponent)
		{
			return foundComponent;
		}
		static_assert(std::is_base_of<Component, T>::value && "T must inherit from Component");

		auto component = std::make_shared<T>(this);
		m_Components.emplace_back(component);

		return component;
	}

	template<typename T>
	inline std::shared_ptr <T> dae::GameObject::GetComponent()
	{
		for (auto& component : m_Components)
		{
			std::shared_ptr<T> castComponent = std::dynamic_pointer_cast<T>(component);
			if (castComponent) return castComponent;
		}

		return nullptr;
	}

	template<typename T>
	inline void dae::GameObject::RemoveComponent()
	{
		if (typeid(T).name() == typeid(Transform).name())
		{
			throw std::invalid_argument("Cannot remove the Transform from a gameobject");
		}

		auto remove = [&](const auto& component) {
			auto castComponent = std::dynamic_pointer_cast<T>(component);

			return castComponent;
			};

		m_Components.erase(std::remove_if(begin(m_Components), end(m_Components), remove), end(m_Components));
	}
}
