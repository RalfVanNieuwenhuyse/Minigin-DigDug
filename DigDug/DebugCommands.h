#pragma once
#include "Command.h"

namespace dae
{
	class LivesComponent;
	class PlayerScore;

	class RemoveLifeCommand : public GameObjectCommand
	{
	public:
		RemoveLifeCommand(GameObject* gameObject);

		void Execute() override;
		
	private:
		std::shared_ptr<LivesComponent> m_Lives{ nullptr };
	};

	class AddScoreCommand : public GameObjectCommand
	{
	public:
		AddScoreCommand(GameObject* gameObject);

		void Execute() override;

	private:
		std::shared_ptr<PlayerScore> m_ScoreComp{ nullptr };
	};

	class EatBoostCommand : public GameObjectCommand
	{
	public:
		EatBoostCommand(GameObject* gameObject);

		void Execute() override;		
	};

	class NextLevelCommand : public Command
	{
	public:
		NextLevelCommand();

		void Execute() override;
	};

	class SinglePlayerCommand : public Command
	{
	public:
		SinglePlayerCommand();

		void Execute() override;
	};

	class MultiPlayerCommand : public Command
	{
	public:
		MultiPlayerCommand();

		void Execute() override;
	};

	class VSPlayerCommand : public Command
	{
	public:
		VSPlayerCommand();

		void Execute() override;
	};
}

