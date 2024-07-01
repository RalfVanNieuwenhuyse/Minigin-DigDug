#pragma once
#include "SoundSystem.h"
#include <memory>

namespace dae
{
    class logging_sound_system final : public sound_system
    {
	public:

		logging_sound_system(std::unique_ptr<sound_system>&& ss);
		~logging_sound_system();

		logging_sound_system(const logging_sound_system& other) = delete;
		logging_sound_system(logging_sound_system&& other) = delete;
		logging_sound_system& operator=(const logging_sound_system& other) = delete;
		logging_sound_system& operator=(logging_sound_system&& other) = delete;

		void Init(const std::string& dataPath) override;
		void Destroy() override;
		void Play(SoundData soundData) override;
		void Mute() override;
		void Load(SoundData soundData) override;

	private:
		std::unique_ptr<sound_system> _ss_instance;
    };
}

