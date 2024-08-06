#pragma once
#include "State.h"
#include <glm/glm.hpp>
#include <random>

namespace dae
{
    class GameObject;
}

namespace rvn
{
    class GridComponent;
    class GridMovement;
    
       

    enum class EPookaState
    {
        Attack,
        Ghost,
        Pump,
        Death
    };

	class PookaStates : public	State
	{
    public:
        virtual ~PookaStates() = default;

        virtual void OnEnter() override {};
        virtual void OnExit() override {};
        virtual void Update() override {};
    protected:
        PookaStates(dae::Component* owner);
	};

    class PookaAttackState final : public PookaStates
    {
    public:
        PookaAttackState(dae::Component* owner);
        virtual void OnEnter() override;
        virtual void OnExit() override;
        virtual void Update() override;
    private:   
        GridMovement* m_MovementComp{ nullptr };
        GridComponent* m_GridComp{ nullptr };
        dae::GameObject* m_Owner{nullptr};

        int m_DirectionIndex{ 0 };
        const std::vector<glm::vec3> m_Directions{ {1,0,0},{-1,0,0},{0,1,0},{0,-1,0} };
        float m_Speed{ 80 };

        static std::mt19937 s_Gen;
        static std::uniform_int_distribution<> s_Distrib;

        bool m_ShouldCheckDirection = true;
    };

    class PookaGhostState final : public PookaStates
    {
    public:
        PookaGhostState(dae::Component* owner);
        virtual void OnEnter() override;
        virtual void OnExit() override;
        virtual void Update() override;
    private:

    };

    class PookaPumpState final : public PookaStates
    {
    public:
        PookaPumpState(dae::Component* owner);
        virtual void OnEnter() override;
        virtual void OnExit() override;
        virtual void Update() override;
    private:

    };

    class PookaDeathState final : public PookaStates
    {
    public:
        PookaDeathState(dae::Component* owner);
        virtual void OnEnter() override;
        virtual void OnExit() override;
        virtual void Update() override;
    private:

    };
}

