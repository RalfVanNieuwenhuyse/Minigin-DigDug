#pragma once
#include "Component.h"
namespace dae
{
    class PlayerScore : public Component
    {
	public:
		PlayerScore(GameObject* owner);

		~PlayerScore() = default;
		PlayerScore(const PlayerScore& other) = delete;
		PlayerScore(PlayerScore&& other) = delete;
		PlayerScore& operator=(const PlayerScore& other) = delete;
		PlayerScore& operator=(PlayerScore&& other) = delete;

		void SetScore(const unsigned int score);
		void AddScore(const unsigned int score);
		unsigned int GetScore();

	private:

		unsigned int m_Score{0};
    };
}