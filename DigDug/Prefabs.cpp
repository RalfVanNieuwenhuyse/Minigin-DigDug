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
#include "FygarComp.h"

#include "DistructionComponent.h"

#include "PumpCommand.h"
#include "Event.h"
#include "EventManager.h"

namespace rvn
{
    namespace Prefab
    {
#pragma region player
        dae::GameObject* Player01(dae::Scene& scene, const glm::vec3& pos, rvn::GridComponent* gridcomp, std::vector<glm::vec3> grid, rvn::GameTypeLevelGen)
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

            auto digdugcomp = player->AddComponent<rvn::DigDug>(); 
            //digdugcomp->SetIsPlayer2(true);
            auto& input = dae::InputManager::GetInstance();

            input.AddKeyboardCommand<rvn::PumpCommand>(std::make_unique<rvn::PumpCommand>(player.get()),
                dae::KeyboardInput{ SDL_SCANCODE_F, dae::ButtonState::Pressed });

            auto collisionpacman = player->AddComponent<dae::Collision>();
            collisionpacman->SetScene(scene.GetName());
            collisionpacman->SetBounds(14, 14);
            collisionpacman->SetLayer("Player");
            collisionpacman->SetCallback([&](const dae::Collision*, const dae::Collision*)
                {

                });

            return player.get();
        }

        void createCharacters(dae::Scene& scene, const glm::vec3& pos, rvn::GridComponent* gridcomp ,std::vector<glm::vec3> grid, rvn::GameTypeLevelGen type)
        {
            const glm::vec3 moveDirectionHor{ 1, 0, 0 };
            const glm::vec3 moveDirectionVert{ 0, 1, 0 };

            auto player = Player01(scene, pos, gridcomp,grid, type);

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

        dae::GameObject* Player02(dae::Scene& scene, const glm::vec3& pos, rvn::GridComponent* gridcomp, std::vector<glm::vec3> grid, rvn::GameTypeLevelGen)
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

            auto digdugcomp = player->AddComponent<rvn::DigDug>();
            digdugcomp->SetIsPlayer2(true);
            auto& input = dae::InputManager::GetInstance();

            input.AddXboxCommand<rvn::PumpCommand>(std::make_unique<rvn::PumpCommand>(player.get()),
                dae::XboxControllerInput{ 0, dae::XboxController::ControllerButton::ButtonA, dae::ButtonState::Pressed });

            auto collisionpacman = player->AddComponent<dae::Collision>();
            collisionpacman->SetScene(scene.GetName());
            collisionpacman->SetBounds(14, 14);
            collisionpacman->SetLayer("Player");
            collisionpacman->SetCallback([&](const dae::Collision*, const dae::Collision*)
                {

                });

            return player.get();
        }

        void createCharacter02(dae::Scene& scene, const glm::vec3& pos, rvn::GridComponent* gridcomp, std::vector<glm::vec3> grid, rvn::GameTypeLevelGen type)
        {
            const glm::vec3 moveDirectionHor{ 1, 0, 0 };
            const glm::vec3 moveDirectionVert{ 0, 1, 0 };

            auto player = Player02(scene, pos, gridcomp, grid, type);

            auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

            auto empty = std::make_shared<dae::GameObject>();
            scene.Add(empty);
            empty->GetTransform()->SetPosition(5, (480.f / 2.f)-200, 1);

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

        dae::GameObject* rvn::Prefab::CreatePumpRight(dae::Scene& scene, const glm::vec3& pos)
        {
            auto pump = std::make_shared<dae::GameObject>();
            scene.Add(pump);

            glm::vec3 newPos = pos;
            newPos.x += 16.f;
            pump->GetTransform()->SetPosition(newPos);

            pump->AddComponent<dae::Image>()->SetTexture("Characters/PumpRight.png");
            pump->AddComponent<dae::ImageRender>();

            auto collision = pump->AddComponent<dae::Collision>();
            collision->SetScene(scene.GetName());
            collision->SetBounds(46, 14);
            collision->SetLayer("Pump");
            collision->SetCallback([&](const dae::Collision*, const dae::Collision* other)
                {
                    if (other->GetLayer() != "Enemy") return;

                    std::shared_ptr<dae::GameObjectEvent> eventPumpHit = std::make_shared<dae::GameObjectEvent>();
                    eventPumpHit->eventType = "PumpHitEnenmy";
                    eventPumpHit->gameObject = other->GetParentGameObject();
                    dae::EventManager::GetInstance().SendEventMessage(std::move(eventPumpHit));
                });

            //pump->AddComponent<rvn::DistructionComponent>()->SetLifeTime(1.f);
            return pump.get();
        }

        dae::GameObject* rvn::Prefab::CreatePumpLeft(dae::Scene& scene, const glm::vec3& pos)
        {
            auto pump = std::make_shared<dae::GameObject>();
            scene.Add(pump);

            glm::vec3 newPos = pos;
            newPos.x -= 48.f;
            pump->GetTransform()->SetPosition(newPos);

            pump->AddComponent<dae::Image>()->SetTexture("Characters/PumpLeft.png");
            pump->AddComponent<dae::ImageRender>();

            auto collision = pump->AddComponent<dae::Collision>();
            collision->SetScene(scene.GetName());
            collision->SetBounds(46, 14);
            collision->SetLayer("Pump");
            collision->SetCallback([&](const dae::Collision*, const dae::Collision* other)
                {
                    if (other->GetLayer() != "Enemy") return;

                    std::shared_ptr<dae::GameObjectEvent> eventPumpHit = std::make_shared<dae::GameObjectEvent>();
                    eventPumpHit->eventType = "PumpHitEnenmy";
                    eventPumpHit->gameObject = other->GetParentGameObject();
                    dae::EventManager::GetInstance().SendEventMessage(std::move(eventPumpHit));
                });
           // pump->AddComponent<rvn::DistructionComponent>()->SetLifeTime(1.f);

            return pump.get();
        }

        dae::GameObject* rvn::Prefab::CreatePumpUp(dae::Scene& scene, const glm::vec3& pos)
        {
            auto pump = std::make_shared<dae::GameObject>();
            scene.Add(pump);

            glm::vec3 newPos = pos;
            newPos.y -= 48.f;
            pump->GetTransform()->SetPosition(newPos);

            pump->AddComponent<dae::Image>()->SetTexture("Characters/PumpUp.png");
            pump->AddComponent<dae::ImageRender>();

            auto collision = pump->AddComponent<dae::Collision>();
            collision->SetScene(scene.GetName());
            collision->SetBounds(14, 46);
            collision->SetLayer("Pump");
            collision->SetCallback([&](const dae::Collision*, const dae::Collision* other)
                {
                    if (other->GetLayer() != "Enemy") return;

                    std::shared_ptr<dae::GameObjectEvent> eventPumpHit = std::make_shared<dae::GameObjectEvent>();
                    eventPumpHit->eventType = "PumpHitEnenmy";
                    eventPumpHit->gameObject = other->GetParentGameObject();
                    dae::EventManager::GetInstance().SendEventMessage(std::move(eventPumpHit));
                });
           // pump->AddComponent<rvn::DistructionComponent>()->SetLifeTime(1.f);

            return pump.get();
        }

        dae::GameObject* rvn::Prefab::CreatePumpDown(dae::Scene& scene, const glm::vec3& pos)
        {
            auto pump = std::make_shared<dae::GameObject>();
            scene.Add(pump);

            glm::vec3 newPos = pos;
            newPos.y += 16.f;
            pump->GetTransform()->SetPosition(newPos);

            pump->AddComponent<dae::Image>()->SetTexture("Characters/PumpDown.png");
            pump->AddComponent<dae::ImageRender>();

            auto collision = pump->AddComponent<dae::Collision>();
            collision->SetScene(scene.GetName());
            collision->SetBounds(14, 46);
            collision->SetLayer("Pump");
            collision->SetCallback([&](const dae::Collision*, const dae::Collision* other)
                {
                    if (other->GetLayer() != "Enemy") return;

                    std::shared_ptr<dae::GameObjectEvent> eventPumpHit = std::make_shared<dae::GameObjectEvent>();
                    eventPumpHit->eventType = "PumpHitEnenmy";
                    eventPumpHit->gameObject = other->GetParentGameObject();
                    dae::EventManager::GetInstance().SendEventMessage(std::move(eventPumpHit));
                });
            //pump->AddComponent<rvn::DistructionComponent>()->SetLifeTime(1.f);


            return pump.get();
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
                    if (other->GetLayer() == "Player") 
                    {
                        std::shared_ptr<dae::GameObjectEvent> event = std::make_shared<dae::GameObjectEvent>();
                        event->eventType = "PlayerCollidedEnemy";
                        event->gameObject = other->GetParentGameObject();
                        dae::EventManager::GetInstance().SendEventMessage(std::move(event));
                    }

                });

            enemy->AddComponent<rvn::PookaComp>();
        }

        void CreateFygar(dae::Scene& scene, const glm::vec3& pos, rvn::GridComponent* gridcomp, rvn::GameTypeLevelGen type )
        {
            const float moveSpeed{ 100 };

            auto enemy = std::make_shared<dae::GameObject>();
            scene.Add(enemy);
            enemy->GetTransform()->SetPosition(pos);

            enemy->AddComponent<dae::Image>()->SetTexture("Enemy/Fygar.png");
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
                    if (other->GetLayer() == "Player")
                    {
                        std::shared_ptr<dae::GameObjectEvent> event = std::make_shared<dae::GameObjectEvent>();
                        event->eventType = "PlayerCollidedEnemy";
                        event->gameObject = other->GetParentGameObject();
                        dae::EventManager::GetInstance().SendEventMessage(std::move(event));
                    }

                });

            auto fygarComp = enemy->AddComponent<rvn::FygarComp>();

            if(type==GameTypeLevelGen::VS) fygarComp->SetIsPlayer2(true);
        }

        void rvn::Prefab::CreateFireBreathRight(dae::Scene& scene, const glm::vec3& pos)
        {
            auto fire = std::make_shared<dae::GameObject>();
            scene.Add(fire);

            glm::vec3 newPos = pos;
            newPos.x += 16.f;
            fire->GetTransform()->SetPosition(newPos);

            fire->AddComponent<dae::Image>()->SetTexture("Enemy/FireBreathRight.png");
            fire->AddComponent<dae::ImageRender>();

            auto collision = fire->AddComponent<dae::Collision>();
            collision->SetScene(scene.GetName());
            collision->SetBounds(46, 14);
            collision->SetLayer("Enemy");
            collision->SetCallback([&](const dae::Collision*, const dae::Collision* other)
                {
                    if (other->GetLayer() != "Player") return;

                    std::shared_ptr<dae::GameObjectEvent> event = std::make_shared<dae::GameObjectEvent>();
                    event->eventType = "PlayerCollidedEnemy";
                    event->gameObject = other->GetParentGameObject();
                    dae::EventManager::GetInstance().SendEventMessage(std::move(event));
                });

            fire->AddComponent<rvn::DistructionComponent>()->SetLifeTime(1.f);

        }

        void rvn::Prefab::CreateFireBreathLeft(dae::Scene& scene, const glm::vec3& pos)
        {
            auto fire = std::make_shared<dae::GameObject>();
            scene.Add(fire);

            glm::vec3 newPos = pos;
            newPos.x -= 48.f;
            fire->GetTransform()->SetPosition(newPos);

            fire->AddComponent<dae::Image>()->SetTexture("Enemy/FireBreathLeft.png");
            fire->AddComponent<dae::ImageRender>();

            auto collision = fire->AddComponent<dae::Collision>();
            collision->SetScene(scene.GetName());
            collision->SetBounds(46, 14);
            collision->SetLayer("Enemy");
            collision->SetCallback([&](const dae::Collision*, const dae::Collision* other)
                {
                    if (other->GetLayer() != "Player") return;

                    std::shared_ptr<dae::GameObjectEvent> event = std::make_shared<dae::GameObjectEvent>();
                    event->eventType = "PlayerCollidedEnemy";
                    event->gameObject = other->GetParentGameObject();
                    dae::EventManager::GetInstance().SendEventMessage(std::move(event));
                });

            fire->AddComponent<rvn::DistructionComponent>()->SetLifeTime(1.f);

        }

        void rvn::Prefab::CreateFireBreathUp(dae::Scene& scene, const glm::vec3& pos)
        {
            auto fire = std::make_shared<dae::GameObject>();
            scene.Add(fire);

            glm::vec3 newPos = pos;
            newPos.y -= 48.f;
            fire->GetTransform()->SetPosition(newPos);

            fire->AddComponent<dae::Image>()->SetTexture("Enemy/FireBreathUp.png");
            fire->AddComponent<dae::ImageRender>();

            auto collision = fire->AddComponent<dae::Collision>();
            collision->SetScene(scene.GetName());
            collision->SetBounds(14, 46);
            collision->SetLayer("Enemy");
            collision->SetCallback([&](const dae::Collision*, const dae::Collision* other)
                {
                    if (other->GetLayer() != "Player") return;

                    std::shared_ptr<dae::GameObjectEvent> event = std::make_shared<dae::GameObjectEvent>();
                    event->eventType = "PlayerCollidedEnemy";
                    event->gameObject = other->GetParentGameObject();
                    dae::EventManager::GetInstance().SendEventMessage(std::move(event));
                });

            fire->AddComponent<rvn::DistructionComponent>()->SetLifeTime(1.f);

        }

        void rvn::Prefab::CreateFireBreathDown(dae::Scene& scene, const glm::vec3& pos)
        {
            auto fire = std::make_shared<dae::GameObject>();
            scene.Add(fire);

            glm::vec3 newPos = pos;
            newPos.y += 16.f;
            fire->GetTransform()->SetPosition(newPos);

            fire->AddComponent<dae::Image>()->SetTexture("Enemy/FireBreathDown.png");
            fire->AddComponent<dae::ImageRender>();

            auto collision = fire->AddComponent<dae::Collision>();
            collision->SetScene(scene.GetName());
            collision->SetBounds(14, 46);
            collision->SetLayer("Enemy");
            collision->SetCallback([&](const dae::Collision*, const dae::Collision* other)
                {
                    if (other->GetLayer() != "Player") return;

                    std::shared_ptr<dae::GameObjectEvent> event = std::make_shared<dae::GameObjectEvent>();
                    event->eventType = "PlayerCollidedEnemy";
                    event->gameObject = other->GetParentGameObject();
                    dae::EventManager::GetInstance().SendEventMessage(std::move(event));
                });

            fire->AddComponent<rvn::DistructionComponent>()->SetLifeTime(1.f);

        }
#pragma endregion


       

    }//prefab    
}//rvn
