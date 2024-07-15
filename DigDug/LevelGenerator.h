#pragma once
#include <rapidjson/document.h>
#include <glm/glm.hpp>
#include <string>

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
        void generateElement(int element, dae::Scene& scene, const glm::vec3& pos);

    private:
        const std::string m_Filename;
        rapidjson::Document m_Document;
        int m_Width;
        int m_Height;
        float m_Offset;        
	};
}
