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
    enum class GameTypeLevelGen
    {
        Single,
        Multy,
        VS
    };

	class LevelGenerator
	{
    public:

        LevelGenerator(const std::string& filename, const GameTypeLevelGen gameType);

        bool loadLevel();
        void generateLevel(dae::Scene& scene, const glm::vec3& offset);
        void generateElement(int element, dae::Scene& scene, const glm::vec3& pos, std::vector<glm::vec3> grid, int cellIndex);
        std::shared_ptr<rvn::GridComponent> GetGrid() const { return m_Grid; };

        void DEBUG_CheckLevelDug();
        bool IsLevelLoaded() { return m_IsLoaded; }

    private:
        const std::string m_Filename;
        rapidjson::Document m_Document;
        int m_Width{15};
        int m_Height{16};
        float m_Offset{32};
        bool m_IsLoaded{ false };

        std::shared_ptr<rvn::GridComponent> m_Grid;
        GameTypeLevelGen m_GameType;
	};
}
