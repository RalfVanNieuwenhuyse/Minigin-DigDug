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

void loadSounds()
{
	auto& sound_system = dae::servicelocator::get_sound_system();
	sound_system.Play(dae::SoundData{ 0, 0, dae::SoundData::SoundType::SoundEffect, "pacman_death.wav"});
}

void CreateGhost(dae::Scene& scene)
{	
	auto ghost = std::make_shared<dae::GameObject>();
	scene.Add(ghost);
	ghost->AddComponent<dae::Image>()->SetTexture("scaredghost.png");
	ghost->AddComponent<dae::ImageRender>();
	ghost->GetTransform()->SetPosition((640 / 2) + 80, (480 / 2) + 60, 1);
	auto collision = ghost->AddComponent<dae::Collision>();
	collision->SetScene(scene.GetName());
	collision->SetBounds(14, 14);
	collision->SetLayer("Enemy");
	collision->SetCallback([&](const dae::Collision*, const dae::Collision*other)
		{
			if (other->GetLayer() != "Player") return;
			
			std::unique_ptr<dae::GameObjectEvent> event = std::make_unique<dae::GameObjectEvent>();
			event->eventType = "PlayerCollidedGhost";
			event->gameObject = other->GetParentGameObject();
			dae::EventManager::GetInstance().SendEventMessage(std::move(event));
		});
}

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	
	auto fps = std::make_shared<dae::GameObject>();
	scene.Add(fps);	
	auto textFPScomp = fps->AddComponent<dae::Text>();
	textFPScomp->SetFont(font);	
	textFPScomp->SetText("test");
	fps->AddComponent<dae::TextRender>();
	fps->AddComponent<dae::FPS>();
	fps->GetTransform()->SetPosition(0, 420,1);

	/*auto grid = std::make_shared<dae::GameObject>();
	auto gengrid = grid->AddComponent<rvn::GridComponent>()->CreateGrid(12, 12, 32, glm::vec3{100,100,0});
	scene.Add(grid);*/



	rvn::LevelGenerator level1("../Data/Levels/Level_1.json");
	level1.loadLevel();
	level1.generateLevel(scene, glm::vec3{ 100,100,0 });
	level1.DEBUG_CheckLevelDug();

	/*for (auto gridpoint : level1.GetGrid())
	{
		auto point = std::make_shared<dae::GameObject>();
		scene.Add(point);
		point->AddComponent<dae::Image>()->SetTexture("pill.png");
		point->AddComponent<dae::ImageRender>();
		point->GetTransform()->SetPosition(gridpoint);
	}*/


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

	//CreateGhost(scene);
	loadSounds();
}


int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}