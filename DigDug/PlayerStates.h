#pragma once
#include "State.h"
#include <glm/glm.hpp>
#include "Event.h"

namespace rvn
{
    class MoveCommand;
    enum class PlayerState
    {
        Move,
        Pump,
        Die,
        LoseLife
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

        void DamageDigDug(const dae::Event* e);
        void SetToPump(const dae::Event* e);

    };

    class PumpState final : public PlayerStates
    {
    public:
        PumpState(dae::Component* owner);
        virtual void OnEnter() override;
        virtual void OnExit() override;
        virtual void Update() override;
    private:

        dae::GameObject* m_Pump{nullptr};

        const float m_MaxPumpIdle{1.f};
        float m_IdleTimer{};

        const float m_CoolDown{ 0.5f };
        float m_CDTimer{};

        void DamageDigDug(const dae::Event* e);
        void Pump(const dae::Event* e);
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

    class LifeLostState final : public PlayerStates
    {
    public:
        LifeLostState(dae::Component* owner);
        virtual void OnEnter() override;
        virtual void OnExit() override;
        virtual void Update() override;
    private:
        const float m_MaxTime{2.f};
        float m_Timer{ 0 };
    };
}

