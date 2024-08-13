#pragma once
#include "SceneManager.h"

namespace dae
{
	class Collision;
	class GameObject;
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);		
	public:
		void Add(std::shared_ptr<GameObject> object);
		void Remove(std::shared_ptr<GameObject> object);
		void RemoveAll();

		void Update();
		void FixedUpdate();
		void Render() const;
		void RenderImGui() const;

		std::string GetName() const { return m_Name; };

		void AddCollision(Collision* collision);
		void RemoveCollision(Collision* collision);
		std::vector <Collision*> GetCollisions() { return m_Collisions; };


		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);
		void ReorderGameobjects();

		std::string m_Name;
		std::vector < std::shared_ptr<GameObject>> m_objects{};
		std::vector < std::shared_ptr<GameObject>> m_pendingObjects{};
		bool m_WasGameObjectAdded{ false };
		std::vector<Collision*> m_pendingCollisions;
		bool m_WasCollisionAdded = false;

		void ReorderCollisions();  // New method to reorder collisions if needed

		static unsigned int m_idCounter; 

		std::vector <Collision*> m_Collisions{};
	};

}
