#include "State.h"

rvn::State::State(dae::Component* owner)
    :m_owner{owner}
{
}

dae::Component* rvn::State::GetOwnerComponent() const
{
    return m_owner;
}
