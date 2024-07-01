#include "SDL_SoundSytem.h"
#include <stdexcept>
#include <unordered_map>

#include "SDL.h"
#include "../SDL2_mixer/include/SDL_mixer.h"

#define MIX_CHANNEL_GROUP_MUSIC 0
#define MIX_CHANNEL_GROUP_EFFECTS 1

namespace dae
{
	class SDL_sound_system::SDL_sound_systemImpl final
	{
	public:
		void Init();

		void Play(unsigned short id, SoundData::SoundType soundType, float volume);
		void LoadSound(unsigned short id, const std::string& filepath);
		bool IsSoundLoaded(unsigned short id);
		void Mute();
		void Quit();
	private:
		std::unordered_map<unsigned short, Mix_Chunk*> m_LoadedSounds;
		bool m_IsMuted{ false };

	};
}

void dae::SDL_sound_system::SDL_sound_systemImpl::Init()
{
	SDL_version version{};

	SDL_MIXER_VERSION(&version)
		printf("We compiled against SDL_mixer version %u.%u.%u ...\n", version.major, version.minor, version.patch);

	version = *Mix_Linked_Version();
	printf("We are linking against SDL_mixer version %u.%u.%u.\n", version.major, version.minor, version.patch);

	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		throw std::runtime_error(std::string("Failed to load support for audio: ") + SDL_GetError());
	}

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 5, 0) < 0) {
		throw std::runtime_error("Failed to open audio: " + std::string(Mix_GetError()));
	}

	Mix_GroupChannels(0, 0, MIX_CHANNEL_GROUP_MUSIC);
	Mix_GroupChannels(1, 4, MIX_CHANNEL_GROUP_EFFECTS);
}

void dae::SDL_sound_system::SDL_sound_systemImpl::Play(unsigned short id, dae::SoundData::SoundType soundType, float volume)
{
	if (!IsSoundLoaded(id))	printf("Sound not found, load the sound first.\n");

	Mix_Chunk* chunk = m_LoadedSounds[id];

	int mixVolume = static_cast<int>(volume * MIX_MAX_VOLUME);
	Mix_VolumeChunk(chunk, mixVolume);

	int channel{ 0 };
	int repeat{ 1 };
	switch (soundType)
	{
	case SoundData::SoundType::SoundEffect:
		channel = Mix_GroupAvailable(MIX_CHANNEL_GROUP_EFFECTS);
		repeat = 0;
		if (channel == -1)
		{
			channel = 1;
		}
		break;
	}

	Mix_PlayChannel(channel, chunk, repeat);
}

void dae::SDL_sound_system::SDL_sound_systemImpl::LoadSound(unsigned short id, const std::string& filepath)
{
	if (!IsSoundLoaded(id))
	{
		Mix_Chunk* chunk = Mix_LoadWAV(filepath.c_str());
		if (chunk == nullptr)
		{
			printf("Failed to load sound, SDL_mixer Error: %s\n", Mix_GetError());
		}
		m_LoadedSounds[id] = chunk;
	}
}

bool dae::SDL_sound_system::SDL_sound_systemImpl::IsSoundLoaded(unsigned short id)
{
	return m_LoadedSounds.find(id) != m_LoadedSounds.end();
}

void dae::SDL_sound_system::SDL_sound_systemImpl::Mute()
{	
	if (m_IsMuted)
	{
		for (int i = 0; i < 5; i++)
		{
			Mix_Volume(i, 128);
		}
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			Mix_Volume(i, 0);
		}
	}
	m_IsMuted = !m_IsMuted;
}

void dae::SDL_sound_system::SDL_sound_systemImpl::Quit()
{
	for (auto& sound : m_LoadedSounds)
	{
		if (sound.second == nullptr)
		{
			Mix_FreeChunk(sound.second);
			sound.second = nullptr;
		}
	}
	Mix_CloseAudio();
	Mix_Quit();
}

dae::SDL_sound_system::SDL_sound_system()
	:sound_system()
{
}

dae::SDL_sound_system::~SDL_sound_system()
{
	Destroy();
}

void dae::SDL_sound_system::Init(const std::string& dataPath)
{
	m_pImpl = std::make_unique<SDL_sound_systemImpl>();
	m_DataPath = dataPath;
	m_pImpl->Init();

	m_ThreadRunning = true;
	m_SoundThread = std::jthread(&SDL_sound_system::SoundThread, this);
}

void dae::SDL_sound_system::Destroy()
{
	m_ThreadRunning = false;
	m_QueueCondition.notify_all();

	if (m_pImpl)
	{
		m_pImpl->Quit();
	}
}

void dae::SDL_sound_system::Play(SoundData soundData)
{
	std::lock_guard<std::mutex> lock(m_QueueMutex);
	soundData.filePath = m_DataPath + soundData.filePath;
	m_EventQueue.push(soundData);

	m_QueueCondition.notify_all();
}

void dae::SDL_sound_system::Mute()
{
	m_pImpl->Mute();
}

void dae::SDL_sound_system::PlaySound(const SoundData& soundData)
{
	if (!IsSoundLoaded(soundData.id))
	{
		Load(soundData);
	}
	m_pImpl->Play(soundData.id, soundData.soundType, soundData.volume);
}

void dae::SDL_sound_system::Load(SoundData soundData)
{
	if (!IsSoundLoaded(soundData.id))
	{
		soundData.filePath = m_DataPath + soundData.filePath;
		m_pImpl->LoadSound(soundData.id, soundData.filePath);
	}
}

bool dae::SDL_sound_system::IsSoundLoaded(unsigned short id)
{
	return m_pImpl->IsSoundLoaded(id);
}

void dae::SDL_sound_system::SoundThread()
{
	while (m_ThreadRunning)
	{
		std::unique_lock<std::mutex> lock(m_QueueMutex);
		m_QueueCondition.wait(lock, [&]
		{
			if (!m_ThreadRunning) return true;
			return !m_EventQueue.empty();
		});

		if (m_EventQueue.empty()) return;

		SoundData data = m_EventQueue.front();

		m_EventQueue.pop();
		lock.unlock();

		PlaySound(data);
	}
}