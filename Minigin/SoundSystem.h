#pragma once
#include <string>

namespace dae
{
	using sound_id = unsigned short;

	struct SoundData
	{
		enum class SoundType
		{
			Music,
			SoundEffect,
		};

		sound_id id{};
		float volume{ 1 };
		SoundType soundType{ SoundType::SoundEffect };
		std::string filePath{ "" };
		//bool loadFile{ false };
	};

	class sound_system
	{
	public:
		sound_system() = default;
		virtual ~sound_system() = default;

		sound_system(const sound_system& other) = delete;
		sound_system(sound_system&& other) = delete;
		sound_system& operator=(const sound_system& other) = delete;
		sound_system& operator=(sound_system&& other) = delete;

		virtual void Init(const std::string& dataPath) = 0;
		virtual void Destroy() = 0;

		virtual void Play(SoundData soundData) = 0;
		virtual void Mute() = 0;	
		virtual void Load(SoundData soundData) = 0;
	};
}