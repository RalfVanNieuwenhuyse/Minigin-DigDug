#include "Prefabs.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "EventManager.h"
#include "Image.h"
#include "ImageRender.h"
#include "Transform.h"
#include "Text.h"
#include "TextRender.h"
#include "FPS.h"
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

#include "DigDug.h"
#include "PookaComp.h"

namespace rvn
{
    namespace Prefab
    {
#pragma region player
        dae::GameObject* Player01(dae::Scene& scene, const glm::vec3& pos, rvn::GridComponent* gridcomp, std::vector<glm::vec3> grid)
        {

            const float moveSpeed{ 80 };
         
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
            gridmove->SetGridComp(gridcomp);

            player->AddComponent<rvn::DigDug>();

            auto& input = dae::InputManager::GetInstance();

            input.AddKeyboardCommand<dae::AddScoreCommand>(std::make_unique<dae::AddScoreCommand>(player.get()),
                dae::KeyboardInput{ SDL_SCANCODE_O, dae::ButtonState::Up });

            auto collisionpacman = player->AddComponent<dae::Collision>();
            collisionpacman->SetScene(scene.GetName());
            collisionpacman->SetBounds(14, 14);
            collisionpacman->SetLayer("Player");
            collisionpacman->SetCallback([&](const dae::Collision*, const dae::Collision*)
                {

                });

            return player.get();
        }

        void createCharacters(dae::Scene& scene, const glm::vec3& pos, rvn::GridComponent* gridcomp ,std::vector<glm::vec3> grid)
        {
            const glm::vec3 moveDirectionHor{ 1, 0, 0 };
            const glm::vec3 moveDirectionVert{ 0, 1, 0 };

            auto player = Player01(scene, pos, gridcomp,grid);

            auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

            auto empty = std::make_shared<dae::GameObject>();
            scene.Add(empty);
            empty->GetTransform()->SetPosition(5, (480.f / 2.f), 1);

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
        }
#pragma endregion

#pragma region Terrain

        void createWall00(dae::Scene& scene, const glm::vec3& pos)
        {
            auto wall = std::make_shared<dae::GameObject>();
            scene.Add(wall);
            wall->AddComponent<dae::Image>()->SetTexture("World/WorldTile0.png");
            wall->AddComponent<dae::ImageRender>();
            wall->GetTransform()->SetPosition(pos);
        }

        void createWall01(dae::Scene& scene, const glm::vec3& pos)
        {
            auto wall = std::make_shared<dae::GameObject>();
            scene.Add(wall);
            wall->AddComponent<dae::Image>()->SetTexture("World/WorldTile1.png");
            wall->AddComponent<dae::ImageRender>();
            wall->GetTransform()->SetPosition(pos);
        }

        void createWall02(dae::Scene& scene, const glm::vec3& pos)
        {
            auto wall = std::make_shared<dae::GameObject>();
            scene.Add(wall);
            wall->AddComponent<dae::Image>()->SetTexture("World/WorldTile2.png");
            wall->AddComponent<dae::ImageRender>();
            wall->GetTransform()->SetPosition(pos);
        }

        void createWall03(dae::Scene& scene, const glm::vec3& pos)
        {
            auto wall = std::make_shared<dae::GameObject>();
            scene.Add(wall);
            wall->AddComponent<dae::Image>()->SetTexture("World/WorldTile3.png");
            wall->AddComponent<dae::ImageRender>();
            wall->GetTransform()->SetPosition(pos);
        }

        void createDugSpace(dae::Scene& scene, const glm::vec3& pos)
        {
            auto wall = std::make_shared<dae::GameObject>();
            scene.Add(wall);
            wall->AddComponent<dae::Image>()->SetTexture("World/DiggedArea.png");
            wall->AddComponent<dae::ImageRender>();
            wall->GetTransform()->SetPosition(pos);
        }
#pragma endregion

#pragma region Enemy
        void CreatePooka(dae::Scene& scene, const glm::vec3& pos, rvn::GridComponent* gridcomp)
        {
            const float moveSpeed{ 100 };

            auto enemy = std::make_shared<dae::GameObject>();
            scene.Add(enemy);
            enemy->GetTransform()->SetPosition(pos);

            enemy->AddComponent<dae::Image>()->SetTexture("Enemy/pooka.png");
            enemy->AddComponent<dae::ImageRender>();
            //enemy->AddComponent<dae::LivesComponent>()->SetLives(0);
            auto gridmove = enemy->AddComponent<rvn::GridMovement>();
            gridmove->SetSpeed(moveSpeed);
            gridmove->SetGrid(gridcomp->GetGrid());
            gridmove->SetGridComp(gridcomp);

            auto collision = enemy->AddComponent<dae::Collision>();
            collision->SetScene(scene.GetName());
            collision->SetBounds(14, 14);
            collision->SetLayer("Enemy");
            collision->SetCallback([&](const dae::Collision*, const dae::Collision* other)
                {
                    if (other->GetLayer() != "Player") return;

                    std::unique_ptr<dae::GameObjectEvent> event = std::make_unique<dae::GameObjectEvent>();
                    event->eventType = "PlayerCollidedEnemy";
                    event->gameObject = other->GetParentGameObject();
                    dae::EventManager::GetInstance().SendEventMessage(std::move(event));
                });

            enemy->AddComponent<rvn::PookaComp>();
        }

        void CreateFygar(dae::Scene& scene, const glm::vec3& pos, rvn::GridComponent* gridcomp)
        {
            const float moveSpeed{ 100 };

            auto enemy = std::make_shared<dae::GameObject>();
            scene.Add(enemy);
            enemy->GetTransform()->SetPosition(pos);

            enemy->AddComponent<dae::Image>()->SetTexture("Enemy/Fygar.png");
            enemy->AddComponent<dae::ImageRender>();

            enemy->AddComponent<dae::LivesComponent>()->SetLives(0);

            auto gridmove = enemy->AddComponent<rvn::GridMovement>();
            gridmove->SetSpeed(moveSpeed);
            gridmove->SetGrid(gridcomp->GetGrid());
            gridmove->SetGridComp(gridcomp);

            auto collision = enemy->AddComponent<dae::Collision>();
            collision->SetScene(scene.GetName());
            collision->SetBounds(14, 14);
            collision->SetLayer("Enemy");
            collision->SetCallback([&](const dae::Collision*, const dae::Collision* other)
                {
                    if (other->GetLayer() != "Player") return;

                    std::unique_ptr<dae::GameObjectEvent> event = std::make_unique<dae::GameObjectEvent>();
                    event->eventType = "PlayerCollidedEnemy";
                    event->gameObject = other->GetParentGameObject();
                    dae::EventManager::GetInstance().SendEventMessage(std::move(event));
                });
        }
#pragma endregion


    }//prefab    
}//rvn
