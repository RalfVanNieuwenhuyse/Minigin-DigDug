#include "logging_sound_system.h"
#include <iostream>

dae::logging_sound_system::logging_sound_system(std::unique_ptr<sound_system>&& ss)
{
	_ss_instance = std::move(ss);
}

dae::logging_sound_system::~logging_sound_system()
{
	Destroy();
}

void dae::logging_sound_system::Init(const std::string& dataPath)
{
	_ss_instance->Init(dataPath);
}

void dae::logging_sound_system::Destroy()
{
	_ss_instance->Destroy();
}

void dae::logging_sound_system::Play(SoundData soundData)
{
	std::cout << "Playing sound: id " << soundData.id << " at volume " << soundData.volume << "\n";
	_ss_instance->Play(soundData);
}

void dae::logging_sound_system::Mute()
{
	std::cout << "Mute \n";
	_ss_instance->Mute();
}

void dae::logging_sound_system::Load(SoundData soundData)
{
	std::cout << "loading sound: id " << soundData.id << " filepath " << soundData.filePath << "\n";
	_ss_instance->Load(soundData);
}
