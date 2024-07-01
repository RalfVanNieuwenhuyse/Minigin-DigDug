#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update()
{
	if (m_activeScene)
	{
		m_activeScene->Update();
	}
}

void dae::SceneManager::FixedUpdate()
{
	if (m_activeScene)
	{
		m_activeScene->FixedUpdate();
	}
}

void dae::SceneManager::Render()
{
	if (m_activeScene)
	{
		m_activeScene->Render();
	}
}

void dae::SceneManager::RenderImGui()
{
	if (m_activeScene)
	{
		m_activeScene->RenderImGui();
	}
}

void dae::SceneManager::SetActiveScene(const std::string& name)
{
	auto it = m_sceneMap.find(name);
	if (it != m_sceneMap.end())
	{
		m_activeScene = it->second;
	}
	
}

dae::Scene& dae::SceneManager::GetActiveScene() const
{	
	return *m_activeScene;
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_sceneMap[name] = scene;

	// If no active scene is set, make this the active scene
	if (!m_activeScene)
	{
		m_activeScene = scene;
	}

	return *scene;
}


dae::Scene* dae::SceneManager::GetScene(const std::string& name) const
{	
	auto it = m_sceneMap.find(name);
	if (it != m_sceneMap.end())
	{
		return it->second.get();
	}	
	return nullptr;
	
}
