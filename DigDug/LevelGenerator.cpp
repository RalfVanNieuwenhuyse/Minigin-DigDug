#include "LevelGenerator.h"
#include <iostream>
#include <fstream>
#include "rapidjson/filereadstream.h"

//#include "Transform.h"
//#include"Image.h"
//#include "ImageRender.h"
//#include"Collision.h"
//
//#include "PlayerScore.h"

//#include "Event.h"
//#include "EventManager.h"
#include "Scene.h"
#include "Prefabs.h"


#include <iostream>

rvn::LevelGenerator::LevelGenerator(const std::string& filename)
    :m_Filename(filename)
{
}

bool rvn::LevelGenerator::loadLevel()
{
    std::ifstream ifs(m_Filename);
    if (!ifs.is_open()) {
        std::cerr << "Could not open file." << std::endl;
        return false;
    }

    std::string jsonContent((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    ifs.close();

    m_Document.Parse(jsonContent.c_str());

    if (!m_Document.IsObject() || !m_Document.HasMember("grid")) {
        std::cerr << "Invalid JSON format." << std::endl;
        return false;
    }

    const rapidjson::Value& grid = m_Document["grid"];
    if (!grid.IsArray()) {
        std::cerr << "Invalid grid format." << std::endl;
        return false;
    }

    m_Offset = m_Document["offset"].GetFloat();
    m_Width = m_Document["width"].GetInt();
    m_Height = m_Document["height"].GetInt();

    return true;
}

void rvn::LevelGenerator::generateLevel(dae::Scene& scene, const glm::vec3& offset)//thank the ai overlords chatgpt
{
    if (!m_Document.IsObject() || !m_Document.HasMember("grid")) {
        std::cerr << "No level data loaded." << std::endl;
        return;
    }

    auto gridcomp = std::make_shared<dae::GameObject>();
    m_Grid = gridcomp->AddComponent<rvn::GridComponent>();
    m_Grid->CreateGrid(m_Height, m_Width, m_Offset, glm::vec3{ 100,100,0 });
    scene.Add(gridcomp);

    const rapidjson::Value& grid = m_Document["grid"];

    for (rapidjson::SizeType y = 0; y < grid.Size(); ++y) {
        const rapidjson::Value& row = grid[y];
        for (rapidjson::SizeType x = 0; x < row.Size(); ++x) {
            int element = row[x].GetInt();
            glm::vec3 position = offset + glm::vec3(x * m_Offset, y * m_Offset, 0.0f);
            generateElement(element, scene, position, m_Grid->GetGrid(), y * row.Size() + x);
        }
    }
}

void rvn::LevelGenerator::generateElement(int element, dae::Scene& scene, const glm::vec3& pos, std::vector<glm::vec3> grid, int cellIndex)
{
    switch (element) {
    case 1:
        //Createplayer;
        glm::vec3 newPosPlayer = pos;
        newPosPlayer.z += 1.f;
        rvn::Prefab::createCharacters(scene, newPosPlayer, m_Grid.get(), grid);
        m_Grid->DigCell(cellIndex,scene);
        break;
    case 2:
        //CreateEmpty;
        m_Grid->DigCell(cellIndex,scene);
        
        break;
    case 3:
        //CreateWalltype0
        rvn::Prefab::createWall00(scene, pos);
        break;
    case 4:
        //CreateWalltype1
        rvn::Prefab::createWall01(scene, pos);
        break;
    case 5:
        //CreateWalltype2
        rvn::Prefab::createWall02(scene, pos);
        break;
    case 6:
        //CreateWalltype3
        rvn::Prefab::createWall03(scene, pos);
        break;

    case 7:
        //create pooka
        glm::vec3 newPosEnemy = pos;
        newPosEnemy.z += 1.f;
        rvn::Prefab::CreatePooka(scene, newPosEnemy, m_Grid.get());
        m_Grid->DigCell(cellIndex, scene);
        break;
    case 8:
        //create fygar
        //rvn::Prefab::CreateFygar(scene, pos, m_Grid.get());
        break;
    default:
        m_Grid->DigCell(cellIndex,scene);
        break;
    }
}

void rvn::LevelGenerator::DEBUG_CheckLevelDug()
{
    const int width = m_Width;
    const int height = m_Height;
    for (int y = 0; y < height; ++y) {

        for (int x = 0; x < width; ++x) {

            std::cout << m_Grid->IsCellDug(y * width + x) << " ";
        }

        std::cout << std::endl;
    }
}
