#pragma once
#include "Command.h"
#include <glm/glm.hpp>
#include "Event.h"

namespace rvn
{
	class PumpCommand : public dae::GameObjectCommand
	{
	public:
		PumpCommand(dae::GameObject* gameObject);

		void Execute() override;

	private:
		
		bool m_IsShot{ false };

		//void ResetPump(const dae::Event* e);
	};
	
}

