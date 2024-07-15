#pragma once
#include <rapidjson/document.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "GridComponent.h"

namespace dae
{
    class Scene;
}

namespace rvn
{
	class LevelGenerator
	{
    public:

        LevelGenerator(const std::string& filename);

        bool loadLevel();
        void generateLevel(dae::Scene& scene, const glm::vec3& offset);
        void generateElement(int element, dae::Scene& scene, const glm::vec3& pos, std::vector<glm::vec3> grid, int cellIndex);
        std::shared_ptr<rvn::GridComponent> GetGrid() const { return m_Grid; };

        void DEBUG_CheckLevelDug();

    private:
        const std::string m_Filename;
        rapidjson::Document m_Document;
        int m_Width{15};
        int m_Height{16};
        float m_Offset{32};

        std::shared_ptr<rvn::GridComponent> m_Grid;
        
	};
}
