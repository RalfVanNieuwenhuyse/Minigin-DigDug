#include "GameMode.h"
#include "Prefabs.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "InputManager.h"

#include "EventManager.h"


#include "Scene.h"
#include "Image.h"
#include "ImageRender.h"
#include "Transform.h"
#include "Text.h"
#include "TextRender.h"
#include "InputManager.h"
#include "DebugCommands.h"


void rvn::GameMode::Init()
{
	m_LevelGens.push_back(LevelGenerator("../Data/Levels/Level_1.json", rvn::GameTypeLevelGen::Single));
	m_LevelGens.push_back(LevelGenerator("../Data/Levels/Level_2.json", rvn::GameTypeLevelGen::Single));
	m_LevelGens.push_back(LevelGenerator("../Data/Levels/Level_3.json", rvn::GameTypeLevelGen::Single));

	m_LevelGens.push_back(LevelGenerator("../Data/Levels/Level_M_1.json", rvn::GameTypeLevelGen::Multy));
	m_LevelGens.push_back(LevelGenerator("../Data/Levels/Level_M_2.json", rvn::GameTypeLevelGen::Multy));
	m_LevelGens.push_back(LevelGenerator("../Data/Levels/Level_M_3.json", rvn::GameTypeLevelGen::Multy));

	m_LevelGens.push_back(LevelGenerator("../Data/Levels/Level_VS_1.json", rvn::GameTypeLevelGen::VS));
	m_LevelGens.push_back(LevelGenerator("../Data/Levels/Level_VS_2.json", rvn::GameTypeLevelGen::VS));
	m_LevelGens.push_back(LevelGenerator("../Data/Levels/Level_VS_3.json", rvn::GameTypeLevelGen::VS));

	

	for (const auto& name : m_SceneNames )
	{
		dae::SceneManager::GetInstance().CreateScene(name);
	}

	/*for (size_t i = 0; i < m_LevelGens.size(); i++)
	{
		m_LevelGens[i].loadLevel();

		auto& scene = *dae::SceneManager::GetInstance().GetScene(m_SceneNames[i + 1]);
		m_LevelGens[i].generateLevel(scene, glm::vec3{ 100,100,0 });
	}*/

	dae::InputManager::GetInstance().AddKeyboardCommand<dae::NextLevelCommand>(std::make_unique<dae::NextLevelCommand>(),
		dae::KeyboardInput{ SDL_SCANCODE_F1, dae::ButtonState::Up });

	dae::InputManager::GetInstance().AddKeyboardCommand<dae::SinglePlayerCommand>(std::make_unique<dae::SinglePlayerCommand>(),
		dae::KeyboardInput{ SDL_SCANCODE_F7, dae::ButtonState::Up });
	dae::InputManager::GetInstance().AddKeyboardCommand<dae::MultiPlayerCommand>(std::make_unique<dae::MultiPlayerCommand>(),
		dae::KeyboardInput{ SDL_SCANCODE_F8, dae::ButtonState::Up });
	dae::InputManager::GetInstance().AddKeyboardCommand<dae::VSPlayerCommand>(std::make_unique<dae::VSPlayerCommand>(),
		dae::KeyboardInput{ SDL_SCANCODE_F9, dae::ButtonState::Up });

}

void rvn::GameMode::MainMenu()
{
	auto& scene = *dae::SceneManager::GetInstance().GetScene(m_SceneNames[0]);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto smallerFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	{
		auto Title = std::make_shared<dae::GameObject>();
		scene.Add(Title);
		auto TitleText = Title->AddComponent<dae::Text>();
		TitleText->SetFont(font);
		TitleText->SetText("DigDug");
		Title->AddComponent<dae::TextRender>();
		Title->GetTransform()->SetPosition(5, 60, 1);
	}

	{
		auto tooltip = std::make_shared<dae::GameObject>();
		scene.Add(tooltip);
		auto tooltipText = tooltip->AddComponent<dae::Text>();
		tooltipText->SetFont(smallerFont);
		tooltipText->SetText("Singleplayer press: F7");
		tooltip->AddComponent<dae::TextRender>();
		tooltip->GetTransform()->SetPosition(5, 120, 1);
	}

	{
		auto tooltip = std::make_shared<dae::GameObject>();
		scene.Add(tooltip);
		auto tooltipText = tooltip->AddComponent<dae::Text>();
		tooltipText->SetFont(smallerFont);
		tooltipText->SetText("Multiplayer press: F8");
		tooltip->AddComponent<dae::TextRender>();
		tooltip->GetTransform()->SetPosition(5, 160, 1);
	}

	{
		auto tooltip = std::make_shared<dae::GameObject>();
		scene.Add(tooltip);
		auto tooltipText = tooltip->AddComponent<dae::Text>();
		tooltipText->SetFont(smallerFont);
		tooltipText->SetText("VSplayer press: F9");
		tooltip->AddComponent<dae::TextRender>();
		tooltip->GetTransform()->SetPosition(5, 200, 1);
	}
}

void rvn::GameMode::NextLevel()
{
	++m_CurrentScene;
	dae::SceneManager::GetInstance().SetActiveScene(m_SceneNames[m_CurrentScene]);


	m_LevelGens[m_CurrentScene-1].loadLevel();
	auto& scene = *dae::SceneManager::GetInstance().GetScene(m_SceneNames[m_CurrentScene]);
	m_LevelGens[m_CurrentScene-1].generateLevel(scene, glm::vec3{ 100,100,0 });
}


void rvn::GameMode::SinglePlayer()
{
	m_CurrentScene = 1;
	dae::SceneManager::GetInstance().SetActiveScene(m_SceneNames[1]);
	m_LevelGens[0].loadLevel();
	auto& scene = *dae::SceneManager::GetInstance().GetScene(m_SceneNames[1]);
	m_LevelGens[0].generateLevel(scene, glm::vec3{ 100,100,0 });
	m_GameType = GameType::Single;
}

void rvn::GameMode::MultiPlayer()
{
	m_CurrentScene = 4;
	dae::SceneManager::GetInstance().SetActiveScene(m_SceneNames[4]);
	m_LevelGens[3].loadLevel();
	auto& scene = *dae::SceneManager::GetInstance().GetScene(m_SceneNames[4]);
	m_LevelGens[3].generateLevel(scene, glm::vec3{ 100,100,0 });
	m_GameType = GameType::Multy;
}

void rvn::GameMode::VSPlayer()
{
	m_CurrentScene = 7;

	dae::SceneManager::GetInstance().SetActiveScene(m_SceneNames[7]);
	m_LevelGens[6].loadLevel();
	auto& scene = *dae::SceneManager::GetInstance().GetScene(m_SceneNames[8]);
	m_LevelGens[6].generateLevel(scene, glm::vec3{ 100,100,0 });
	m_GameType = GameType::VS;
}
