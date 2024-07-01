#pragma once
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include "Singleton.h"


namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Update();
		void FixedUpdate();
		void Render();
		void RenderImGui();

		void SetActiveScene(const std::string& name);
		Scene& GetActiveScene() const;
		Scene* GetScene(const std::string& name) const;
		std::unordered_map<std::string, std::shared_ptr<Scene>> GetScenes() const { return m_sceneMap; }

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;		

		std::unordered_map<std::string, std::shared_ptr<Scene>> m_sceneMap;
		std::shared_ptr<Scene> m_activeScene;
	};
}
