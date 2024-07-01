#pragma once
#include "GameObject.h"
namespace rvn
{
	class State
	{
	public:
		virtual ~State() = default;
		virtual void OnEnter() = 0;
		virtual void OnExit() = 0;
		virtual void Update() = 0;
	protected:

		explicit State(dae::Component* owner);
		dae::Component* GetOwnerComponent() const;
	private:
		dae::Component* m_owner;
	};
}
