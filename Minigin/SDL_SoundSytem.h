#pragma once
#include "SoundSystem.h"
#include <memory>
#include <string>
#include <thread>
#include <queue>
#include <mutex>

namespace dae
{
	class SDL_sound_system final : public sound_system
	{
	public:
		SDL_sound_system();
		~SDL_sound_system();

		SDL_sound_system(const SDL_sound_system& other) = delete;
		SDL_sound_system(SDL_sound_system&& other) = delete;
		SDL_sound_system& operator=(const SDL_sound_system& other) = delete;
		SDL_sound_system& operator=(SDL_sound_system&& other) = delete;
		
		void Init(const std::string& dataPath) override;
		void Destroy() override;
		void Play(SoundData soundData) override;
		void Mute() override;
		void Load(SoundData soundData) override;

	private:
		class SDL_sound_systemImpl;

		std::string m_DataPath;

		std::queue<SoundData> m_EventQueue;
		std::mutex m_QueueMutex;
		std::condition_variable m_QueueCondition;
		std::atomic<bool> m_ThreadRunning{ false };

		std::jthread m_SoundThread;
		void SoundThread();

		std::unique_ptr<SDL_sound_systemImpl> m_pImpl{ nullptr };

		bool IsSoundLoaded(unsigned short id);
		void PlaySound(const SoundData& soundData);		
	};
}

