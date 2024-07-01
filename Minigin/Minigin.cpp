#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Minigin.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "EventManager.h"

#include "ServiceLocator.h"
#include "SDL_SoundSytem.h"
#include "logging_sound_system.h"



#include "GTime.h"
#include <thread>
#include <chrono>



SDL_Window* g_window{};

std::unique_ptr<dae::sound_system> dae::servicelocator::_ss_instance{ std::make_unique<NullSoundSystem>() };

void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version);
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
	printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

dae::Minigin::Minigin(const std::string &dataPath)
{
	
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		640,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);

	ResourceManager::GetInstance().Init(dataPath);

#if _DEBUG
	servicelocator::register_sound_system(std::make_unique<logging_sound_system>(std::make_unique<SDL_sound_system>()));
#else
	servicelocator::register_sound_system(std::make_unique<SDL_sound_system>());
#endif


	servicelocator::get_sound_system().Init(dataPath);
}

dae::Minigin::~Minigin()
{
	Renderer::GetInstance().Destroy();
	servicelocator::get_sound_system().Destroy();

	for (const auto& pair : SceneManager::GetInstance().GetScenes()) 
	{
		pair.second->RemoveAll();		
	}

	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run(const std::function<void()>& load)
{
	load();

	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();
	auto& time = GTime::GetInstance();
	auto& eventManager = EventManager::GetInstance();

	bool doContinue = true;
	float lag{ 0 };
	while (doContinue)
	{		
		time.Update();
		doContinue = input.ProcessInput();

		lag += time.GetDeltaTime();
		while (lag >= time.GetTimeStep())
		{
			sceneManager.FixedUpdate();
			lag -= time.GetTimeStep();
		}
				
		sceneManager.Update();
		renderer.Render();

		eventManager.HandleEvents();

		auto sleepTime = time.GetLastTimeStamp() + std::chrono::milliseconds(time.GetFrameTime()) - std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(sleepTime);		
	}
}
