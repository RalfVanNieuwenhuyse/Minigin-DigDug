#pragma once
#include "Component.h"
#include <map>


namespace dae
{

    class TrashTheCache : public Component
    {
	public:
#pragma region ClassesAndStructs
		struct Transform
		{
			float matrix[16] =
			{ 1,0,0,0,
			1,0,0,0,
			1,0,0,0,
			1,0,0,0, };
		};

		class GameObject3D
		{
		public:
			Transform transform;
			int ID;
		};

		class GameObject3DAlt
		{
		public:
			Transform* transform;
			int ID;
		};
#pragma endregion
		TrashTheCache(GameObject* owner);

		~TrashTheCache() = default;
		TrashTheCache(const TrashTheCache& other) = delete;
		TrashTheCache(TrashTheCache&& other) = delete;
		TrashTheCache& operator=(const TrashTheCache& other) = delete;
		TrashTheCache& operator=(TrashTheCache&& other) = delete;
		
		virtual void RenderImGui() override;

	private:
		void PlotTimes(const std::vector<float>& times, const char* label);
		void DoublePlot(const std::vector<float>& times1 , const std::vector<float>& times2, const char* label);
		void RenderExercise1();
		void Exercise1();
		void RenderExercise2();
		void GameObjects3D();
		void GameObjects3DAlt();

		void HandleTimings(const std::map<int, std::vector<float>>& timings, std::vector<float>& resultVec);
		
		const int ARRAY_SIZE = 10000000;
		const std::vector<float> TIME_STEPS{ 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024 };

		std::vector<float> m_Ex1Times{};
		int m_Ex1Samples{ 10 };		
		std::atomic<bool> m_exercise1IsRunning{ false };

		std::vector<float> m_Ex2Times{};
		std::vector<float> m_Ex2AltTimes{};		
		int m_Ex2Samples{ 10 };
		std::atomic<bool> m_exercise2IsRunning{ false };
		std::atomic<bool> m_exercise2AltIsRunning{ false };
		
    };
}

