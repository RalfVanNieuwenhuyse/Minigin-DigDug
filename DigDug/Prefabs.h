#pragma once
#include "Scene.h"
#include <vector>
#include <glm/vec3.hpp>
#include "LevelGenerator.h"

namespace rvn
{
    class GridComponent;
    namespace Prefab
    {
        dae::GameObject* Player01(dae::Scene& scene, const glm::vec3& pos, rvn::GridComponent* gridcomp, std::vector<glm::vec3> grid,rvn::GameTypeLevelGen type);
        void createCharacters(dae::Scene& scene, const glm::vec3& pos, rvn::GridComponent* gridcomp, std::vector<glm::vec3> grid, rvn::GameTypeLevelGen type);
        dae::GameObject* Player02(dae::Scene& scene, const glm::vec3& pos, rvn::GridComponent* gridcomp, std::vector<glm::vec3> grid, rvn::GameTypeLevelGen type);
        void createCharacter02(dae::Scene& scene, const glm::vec3& pos, rvn::GridComponent* gridcomp, std::vector<glm::vec3> grid, rvn::GameTypeLevelGen type);
        
        void createWall00(dae::Scene& scene, const glm::vec3& pos);
        void createWall01(dae::Scene& scene, const glm::vec3& pos);
        void createWall02(dae::Scene& scene, const glm::vec3& pos);
        void createWall03(dae::Scene& scene, const glm::vec3& pos);
        void createDugSpace(dae::Scene& scene, const glm::vec3& pos);
        
        void CreatePooka(dae::Scene& scene, const glm::vec3& pos, rvn::GridComponent* gridcomp);
        void CreateFygar(dae::Scene& scene, const glm::vec3& pos, rvn::GridComponent* gridcomp, rvn::GameTypeLevelGen type);

        void CreateFireBreathRight(dae::Scene& scene, const glm::vec3& pos);
        void CreateFireBreathLeft(dae::Scene& scene, const glm::vec3& pos);
        void CreateFireBreathUp(dae::Scene& scene, const glm::vec3& pos);
        void CreateFireBreathDown(dae::Scene& scene, const glm::vec3& pos);

        dae::GameObject* CreatePumpRight(dae::Scene& scene, const glm::vec3& pos);
        dae::GameObject* CreatePumpLeft(dae::Scene& scene, const glm::vec3& pos);
        dae::GameObject* CreatePumpUp(dae::Scene& scene, const glm::vec3& pos);
        dae::GameObject* CreatePumpDown(dae::Scene& scene, const glm::vec3& pos);
    }
}
