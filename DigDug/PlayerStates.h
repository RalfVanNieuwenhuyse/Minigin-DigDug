#pragma once
#include "State.h"
#include <glm/glm.hpp>

namespace rvn
{
    class MoveCommand;
    enum class PlayerState
    {
        Move,
        Pump,
        Die
    };

	class PlayerStates : public State
	{
    public:
        virtual ~PlayerStates() = default;

        virtual void OnEnter() override {};
        virtual void OnExit() override {};
        virtual void Update() override {};
    protected:
        PlayerStates(dae::Component* owner);
	};

    class MoveState final : public PlayerStates
    {
    public:
        MoveState(dae::Component* owner);
        virtual void OnEnter() override;
        virtual void OnExit() override;
        virtual void Update() override;
    private:
        glm::vec3 m_OldPos{};
        float m_MoveSpeed{100.f};
        MoveCommand* m_UpCommand{nullptr};
        MoveCommand* m_DownCommand{ nullptr };
        MoveCommand* m_RightCommand{ nullptr };
        MoveCommand* m_LeftCommand{ nullptr };

    };

    class PumpState final : public PlayerStates
    {
    public:
        PumpState(dae::Component* owner);
        virtual void OnEnter() override;
        virtual void OnExit() override;
        virtual void Update() override;
    private:
    };

    class DieState final : public PlayerStates
    {
    public:
        DieState(dae::Component* owner);
        virtual void OnEnter() override;
        virtual void OnExit() override;
        virtual void Update() override;
    private:
    };
}

