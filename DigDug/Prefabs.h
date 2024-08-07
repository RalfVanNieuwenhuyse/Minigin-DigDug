#pragma once
#include "Scene.h"
#include <vector>
#include <glm/vec3.hpp>

namespace rvn
{
    class GridComponent;
    namespace Prefab
    {
        dae::GameObject* Player01(dae::Scene& scene, const glm::vec3& pos, rvn::GridComponent* gridcomp, std::vector<glm::vec3> grid);
        void createCharacters(dae::Scene& scene, const glm::vec3& pos, rvn::GridComponent* gridcomp, std::vector<glm::vec3> grid);
        void createWall00(dae::Scene& scene, const glm::vec3& pos);
        void createWall01(dae::Scene& scene, const glm::vec3& pos);
        void createWall02(dae::Scene& scene, const glm::vec3& pos);
        void createWall03(dae::Scene& scene, const glm::vec3& pos);
        void createDugSpace(dae::Scene& scene, const glm::vec3& pos);
        void CreatePooka(dae::Scene& scene, const glm::vec3& pos, rvn::GridComponent* gridcomp);
        void CreateFygar(dae::Scene& scene, const glm::vec3& pos, rvn::GridComponent* gridcomp);
    }
}
