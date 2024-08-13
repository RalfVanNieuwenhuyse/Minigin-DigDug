#pragma once
#include "Command.h"
#include "FygarComp.h"

namespace rvn
{

	class FireCommand : public dae::GameObjectCommand
	{
	public:
		FireCommand(dae::GameObject* gameObject);

		void Execute() override;

	private:
		std::shared_ptr<FygarComp> m_FygarComp{ nullptr };
		bool m_FirtExicute{ false };
	};
}

