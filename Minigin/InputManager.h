#pragma once
#include <unordered_map>
#include <SDL.h>

#include "Singleton.h"
#include "XboxController.h"
#include "Command.h"

namespace dae
{
	enum class ButtonState
	{
		Up,
		Down,
		Pressed
	};

	struct XboxControllerInput
	{
		unsigned controllerIndex{  };
		XboxController::ControllerButton controllerKey{ };
		ButtonState buttonsState{  };		
	};

	inline bool operator==(const XboxControllerInput& lhs, const XboxControllerInput& rhs)
	{
		return  lhs.controllerIndex == rhs.controllerIndex &&
			lhs.controllerKey == rhs.controllerKey &&
			lhs.buttonsState == rhs.buttonsState;
	}

	struct KeyboardInput
	{
		SDL_Scancode keyboardScancode{ };
		ButtonState buttonsState{ };
	};

	inline bool operator==(const KeyboardInput& lhs, const KeyboardInput& rhs)
	{
		return  lhs.keyboardScancode == rhs.keyboardScancode &&
			lhs.buttonsState == rhs.buttonsState;
	}
}

template<>
struct std::hash<dae::XboxControllerInput>
{
	std::size_t operator()(const dae::XboxControllerInput& input) const
	{
		std::size_t h1 = std::hash<unsigned>{}(input.controllerIndex);
		std::size_t h2 = std::hash<int>{}(static_cast<int>(input.controllerKey));
		std::size_t h3 = std::hash<int>{}(static_cast<int>(input.buttonsState));
		return h1 ^ (h2 << 1) ^ (h3 << 2);
	}
};

template<>
struct std::hash<dae::KeyboardInput>
{
	std::size_t operator()(const dae::KeyboardInput& input) const
	{
		std::size_t h1 = std::hash<unsigned>{}(input.keyboardScancode);
		std::size_t h3 = std::hash<int>{}(static_cast<int>(input.buttonsState));
		return h1 ^ (h3 << 1);
	}
};

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:

		using ControllerCommandsMap = std::unordered_map<XboxControllerInput, std::unique_ptr<Command>>;
		using KeyboardCommandsMap = std::unordered_map<KeyboardInput, std::unique_ptr<Command>>;
				
		unsigned AddController();
		template<typename T> T* AddXboxCommand(std::unique_ptr<T> command, XboxControllerInput input);
		template<typename T> T* AddKeyboardCommand(std::unique_ptr<T> command, KeyboardInput input);

		bool ProcessInput();
	private:
		void HandleConrollerInputs();
		void HandleKeyboardInputs();

		ControllerCommandsMap m_ControllerCommands{ };
		KeyboardCommandsMap m_KeyboardCommands{ };

		std::vector<std::unique_ptr<XboxController>> m_Controllers{};

		std::vector<bool> m_CurrentState{ std::vector<bool>(322, false) };
		std::vector<bool> m_PreviousState{ std::vector<bool>(322, false) };
	};

	template<typename T>
	inline T* InputManager::AddXboxCommand(std::unique_ptr<T> command, XboxControllerInput input)
	{
		static_assert(std::is_base_of<Command, T>::value && "T must inherit from Command");
		while (input.controllerIndex >= m_Controllers.size())
		{
			AddController();
		}

		T* out = command.get();
		m_ControllerCommands[input] = std::move(command);
		return out;
	}

	template<typename T>
	inline T* InputManager::AddKeyboardCommand(std::unique_ptr<T> command, KeyboardInput input)
	{
		static_assert(std::is_base_of<Command, T>::value && "T must inherit from Command");
		T* out = command.get();
		m_KeyboardCommands[input] = std::move(command);
		return out;
	}
}
