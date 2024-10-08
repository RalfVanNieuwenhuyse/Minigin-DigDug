#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"


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
#include "FPS.h"
#include "Rotatetor.h"
#include "TrashTheCache.h"

#include "LivesComponent.h"
#include "LivesUI.h"
#include "PlayerScore.h"
#include "ScoreUI.h"

#include "MoveCommand.h"
#include "DebugCommands.h"

#include "ServiceLocator.h"

#include "GridComponent.h"
#include "GridMovement.h"


#include "Collision.h"

#include <iostream>

#include "LevelGenerator.h"
#include "GameMode.h"

void loadSounds()
{
	auto& sound_system = dae::servicelocator::get_sound_system();
	sound_system.Play(dae::SoundData{ 0, 0, dae::SoundData::SoundType::SoundEffect, "Sound/DeathAnimation.wav"});
	sound_system.Play(dae::SoundData{ 1, 0, dae::SoundData::SoundType::SoundEffect, "Sound/GameOver.wav" });
	sound_system.Play(dae::SoundData{ 2, 0, dae::SoundData::SoundType::SoundEffect, "Sound/Fire.wav" });
	sound_system.Play(dae::SoundData{ 3, 0, dae::SoundData::SoundType::SoundEffect, "Sound/PumpShoot.wav" });
}

void load()
{
	/*auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	
	auto fps = std::make_shared<dae::GameObject>();
	scene.Add(fps);	
	auto textFPScomp = fps->AddComponent<dae::Text>();
	textFPScomp->SetFont(font);	
	textFPScomp->SetText("test");
	fps->AddComponent<dae::TextRender>();
	fps->AddComponent<dae::FPS>();
	fps->GetTransform()->SetPosition(0, 420,1);

	rvn::LevelGenerator level1("../Data/Levels/Level_1.json");
	level1.loadLevel();
	level1.generateLevel(scene, glm::vec3{ 100,100,0 });

#if _DEBUG
	level1.DEBUG_CheckLevelDug();
#endif*/
	

	/*auto fontsmall = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	auto tooltippac = std::make_shared<dae::GameObject>();
	scene.Add(tooltippac);
	auto tooltippacText = tooltippac->AddComponent<dae::Text>();
	tooltippacText->SetFont(fontsmall);
	tooltippacText->SetText("pacman: move wasd, remove life by o");
	tooltippac->AddComponent<dae::TextRender>();
	tooltippac->GetTransform()->SetPosition(5, 60, 1);

	auto tooltipmspac = std::make_shared<dae::GameObject>();
	scene.Add(tooltipmspac);
	auto tooltipmspacText = tooltipmspac->AddComponent<dae::Text>();
	tooltipmspacText->SetFont(fontsmall);
	tooltipmspacText->SetText("mspacman: move dpad, remove life L");
	tooltipmspac->AddComponent<dae::TextRender>();
	tooltipmspac->GetTransform()->SetPosition(5, 85, 0);*/

	//rvn::Prefab::createCharacters(scene, glm::vec3((640 / 2), (480 / 2) + 60, 5), gengrid);
	auto& gamemode = rvn::GameMode::GetInstance();

	gamemode.Init();
	gamemode.MainMenu();
	//gamemode.NextLevel();

	loadSounds();
}


int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}