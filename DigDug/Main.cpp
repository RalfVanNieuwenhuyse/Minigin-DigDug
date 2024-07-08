#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"


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


void loadSounds()
{
	auto& sound_system = dae::servicelocator::get_sound_system();
	sound_system.Play(dae::SoundData{ 0, 0, dae::SoundData::SoundType::SoundEffect, "pacman_death.wav"});
}


dae::GameObject* Player01(dae::Scene& scene, const glm::vec3& pos, std::vector<glm::vec3> grid)
{
	auto& input = dae::InputManager::GetInstance();

	const float moveSpeed{ 100 };
	const glm::vec3 moveDirectionHor{ 1, 0, 0 };
	const glm::vec3 moveDirectionVert{ 0, 1, 0 };

	auto player = std::make_shared<dae::GameObject>();
	scene.Add(player);
	player->AddComponent<dae::Image>()->SetTexture("Characters/DigDug01.png");
	player->AddComponent<dae::ImageRender>();
	player->GetTransform()->SetPosition(pos);
	
	player->AddComponent<dae::LivesComponent>()->SetLives(3);
	player->AddComponent<dae::PlayerScore>()->SetScore(0);

	auto gridmove = player->AddComponent<rvn::GridMovement>();
	gridmove->SetSpeed(moveSpeed);
	gridmove->SetGrid(grid);


	input.AddKeyboardCommand<dae::RemoveLifeCommand>(std::make_unique<dae::RemoveLifeCommand>(player.get()),
		dae::KeyboardInput{ SDL_SCANCODE_O, dae::ButtonState::Up });

	auto pMoveCommand = input.AddKeyboardCommand<rvn::MoveCommand>(std::make_unique<rvn::MoveCommand>(player.get()),
		dae::KeyboardInput{ SDL_SCANCODE_A, dae::ButtonState::Pressed });
	pMoveCommand->SetDirection(-moveDirectionHor);
	pMoveCommand->SetMoveSpeed(moveSpeed);

	pMoveCommand = input.AddKeyboardCommand<rvn::MoveCommand>(std::make_unique<rvn::MoveCommand>(player.get()),
		dae::KeyboardInput{ SDL_SCANCODE_D, dae::ButtonState::Pressed });
	pMoveCommand->SetDirection(moveDirectionHor);
	pMoveCommand->SetMoveSpeed(moveSpeed);

	pMoveCommand = input.AddKeyboardCommand<rvn::MoveCommand>(std::make_unique<rvn::MoveCommand>(player.get()),
		dae::KeyboardInput{ SDL_SCANCODE_W, dae::ButtonState::Pressed });
	pMoveCommand->SetDirection(-moveDirectionVert);
	pMoveCommand->SetMoveSpeed(moveSpeed);

	pMoveCommand = input.AddKeyboardCommand<rvn::MoveCommand>(std::make_unique<rvn::MoveCommand>(player.get()),
		dae::KeyboardInput{ SDL_SCANCODE_S, dae::ButtonState::Pressed });
	pMoveCommand->SetDirection(moveDirectionVert);
	pMoveCommand->SetMoveSpeed(moveSpeed);

	auto collisionpacman = player->AddComponent<dae::Collision>();
	collisionpacman->SetScene(scene.GetName());
	collisionpacman->SetBounds(14, 14);
	collisionpacman->SetLayer("Player");
	collisionpacman->SetCallback([&](const dae::Collision*, const dae::Collision*)
		{

		});

	return player.get();
}

void createCharacters(dae::Scene& scene , const glm::vec3& pos, std::vector<glm::vec3> grid)
{
	//auto& input = dae::InputManager::GetInstance();

	//const float moveSpeed{ 100 };
	const glm::vec3 moveDirectionHor{ 1, 0, 0 };
	const glm::vec3 moveDirectionVert{ 0, 1, 0 };

#pragma region player
	auto player = Player01(scene, pos, grid);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	auto empty = std::make_shared<dae::GameObject>();
	scene.Add(empty);
	empty->GetTransform()->SetPosition(5, (480 / 2), 1);

	auto pacmanLives = std::make_shared<dae::GameObject>();	
	scene.Add(pacmanLives);
	auto textcompPacLives = pacmanLives->AddComponent<dae::Text>();
	textcompPacLives->SetFont(font);
	pacmanLives->AddComponent<dae::TextRender>();
	pacmanLives->AddComponent<dae::LivesUI>()->SetObjectToCheck(player);
	pacmanLives->SetParent(empty.get(), false);

	auto pacmanScore = std::make_shared<dae::GameObject>();
	scene.Add(pacmanScore);
	auto textcompPacScore = pacmanScore->AddComponent<dae::Text>();
	textcompPacScore->SetFont(font);
	pacmanScore->AddComponent<dae::TextRender>();
	pacmanScore->AddComponent<dae::ScoreUI>()->SetObjectToCheck(player);
	pacmanScore->SetParent(empty.get(), false);
	pacmanScore->GetTransform()->SetPosition(0.f, 25.f, 1.f);
#pragma endregion
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


	auto grid = std::make_shared<dae::GameObject>();
	auto gengrid = grid->AddComponent<rvn::GridComponent>()->CreateGrid(12, 12, 32, glm::vec3{100,100,0});
	scene.Add(grid);


	for (auto gridpoint : gengrid)
	{
		auto point = std::make_shared<dae::GameObject>();
		scene.Add(point);
		point->AddComponent<dae::Image>()->SetTexture("pill.png");
		point->AddComponent<dae::ImageRender>();
		point->GetTransform()->SetPosition(gridpoint);
	}


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

	createCharacters(scene, glm::vec3((640 / 2), (480 / 2) + 60, 5), gengrid);
	CreateGhost(scene);
	loadSounds();
}


int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}