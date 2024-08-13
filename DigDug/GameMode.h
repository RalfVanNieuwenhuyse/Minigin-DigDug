#pragma once
#include "Singleton.h"
#include "Event.h"
#include <vector>
//#include "Scene.h"
#include "LevelGenerator.h"

namespace rvn
{
	//class LevelGenerator;

	enum class GameType
	{
		Single,
		Multy,
		VS
	};

	class GameMode : public dae::Singleton<GameMode>
	{
		friend class Singleton<GameMode>;
		GameMode() = default;
	public:
		void Init();

		const GameType GetType() { return m_GameType; };
		void SetGameType(GameType type) { m_GameType = type; };
		void MainMenu();
		void NextLevel();

		void SinglePlayer();
		void MultiPlayer();
		void VSPlayer();

	private:
		GameType m_GameType{GameType::Single};

		int m_CurrentScene{ 0 };
		std::vector<std::string> m_SceneNames{"Menu","Single01","Single02" ,"Single03","Multy01","Multy02" ,"Multy03","VS01","VS02" ,"VS03" };
		std::vector<rvn::LevelGenerator> m_LevelGens{};
		
	};
}

