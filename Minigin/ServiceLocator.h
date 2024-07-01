#pragma once
#include <memory>
#include "SoundSystem.h"
namespace dae
{
	class NullSoundSystem final : public sound_system
	{
		void Init(const std::string&) override {};
		void Play(SoundData soundData) override {};
		void Mute() override {};
		void Destroy() override {};
		void Load(SoundData ) override {};
	};

	class servicelocator final
	{
		static std::unique_ptr<sound_system> _ss_instance;
		
	public:
		static sound_system& get_sound_system() { return *_ss_instance; }
		static void register_sound_system(std::unique_ptr<sound_system>&& ss) {
			_ss_instance = ss == nullptr ? std::make_unique<NullSoundSystem>() : std::move(ss);
		}
	};
}