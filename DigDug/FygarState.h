#pragma once
#include "State.h"
#include <glm/glm.hpp>
#include <random>
#include "Event.h"

namespace rvn
{
    class GridMovement;
    class GridComponent;

    enum class EFygarState
    {
        Attack,
        Fire,
        Ghost,
        Pump,
        Death
    };

	class FygarState : public State
	{
    public:
        virtual ~FygarState() = default;

        virtual void OnEnter() override {};
        virtual void OnExit() override {};
        virtual void Update() override {};
    protected:
        FygarState(dae::Component* owner);
	};

    class FygarAttackState final : public FygarState
    {
    public:
        FygarAttackState(dae::Component* owner);
        virtual void OnEnter() override;
        virtual void OnExit() override;
        virtual void Update() override;
    private:
        GridMovement* m_MovementComp{ nullptr };
        GridComponent* m_GridComp{ nullptr };
        dae::GameObject* m_Owner{ nullptr };

        int m_DirectionIndex{ 0 };
        const std::vector<glm::vec3> m_Directions{ {1,0,0},{-1,0,0},{0,1,0},{0,-1,0} };
        float m_Speed{ 80 };

        static std::mt19937 s_Gen;
        static std::uniform_int_distribution<> s_Distrib;

        float m_BreathCooldown{};
        float m_BreathTimer{};

        void KillDigDug(const dae::Event* e);
    };
    
    class FygarFireState final : public FygarState
    {
    public:
        FygarFireState(dae::Component* owner);
        virtual void OnEnter() override;
        virtual void OnExit() override;
        virtual void Update() override;
    private:
        const float m_MaxTime{ 1.f };
        float m_Timer{ 0 };

        static std::mt19937 s_GenFygarFire;
    };

    class FygarGhostState final : public FygarState
    {
    public:
        FygarGhostState(dae::Component* owner);
        virtual void OnEnter() override;
        virtual void OnExit() override;
        virtual void Update() override;
    private:

    };

    class FygarPumpState final : public FygarState
    {
    public:
        FygarPumpState(dae::Component* owner);
        virtual void OnEnter() override;
        virtual void OnExit() override;
        virtual void Update() override;
    private:

    };

    class FygarDieState final : public FygarState
    {
    public:
        FygarDieState(dae::Component* owner);
        virtual void OnEnter() override;
        virtual void OnExit() override;
        virtual void Update() override;
    private:

    };
}

