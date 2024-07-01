#pragma once
#include <glm/glm.hpp>
#include "Component.h"

namespace dae
{
	class Transform final: public Component
	{
	public:
		Transform(GameObject* owner);

		~Transform() = default;
		Transform(const Transform& other) = delete;
		Transform(Transform&& other) = delete;
		Transform& operator=(const Transform& other) = delete;
		Transform& operator=(Transform&& other) = delete;

		const glm::vec3& GetPosition();
		const glm::vec3& GetLocalPosition() ;
		void SetPosition(float x, float y, float z);
		void SetPosition(const glm::vec3& newPos);
		void SetPositionDirty();

	private:

		void UpdateWorldPosition();

		glm::vec3 m_Position;
		glm::vec3 m_LocalPosition{ 0, 0, 0 };
		bool m_PositionIsDirty{ false };
		//GameObject* m_Owner;
	};
}
