#pragma once
#include "Component.h"
#include "Event.h"

namespace rvn
{
	class PumpCom : public dae::Component
	{
	public:
		PumpCom(dae::GameObject* owner);
		~PumpCom() = default;
		PumpCom(const PumpCom& other) = delete;
		PumpCom(PumpCom&& other) = delete;
		PumpCom& operator=(const PumpCom& other) = delete;
		PumpCom& operator=(PumpCom&& other) = delete;

		void Update() override;

	private:
		
	};
}

