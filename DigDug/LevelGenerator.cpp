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

void rvn::LevelGenerator::generateLevel(dae::Scene& /*scene*/, const glm::vec3& /*offset*/)//thank the ai overlords chatgpt
{
    if (!m_Document.IsObject() || !m_Document.HasMember("grid")) {
        std::cerr << "No level data loaded." << std::endl;
        return;
    }

    //const rapidjson::Value& grid = m_Document["grid"];

    

    
}

void rvn::LevelGenerator::generateElement(int element, dae::Scene& /*scene*/, const glm::vec3& /*pos*/)
{
    switch (element) {
    case 1:
        //Createplayer;
        break;
    case 2:
        //CreateEmpty;
        break;
    case 3:
        //CreateWalltype0
        break;
    case 4:
        //CreateWalltype1
        break;
    case 5:
        //CreateWalltype2
        break;
    case 6:
        //CreateWalltype3
        break;

    case 7:
        
       
        break;
    default:

        break;
    }
}