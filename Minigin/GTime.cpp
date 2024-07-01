#include "GTime.h"

void dae::GTime::Update()
{
	auto now = std::chrono::high_resolution_clock::now();
	m_DeltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(now - m_LastTimestamp).count();
	m_LastTimestamp = now;
}

const float dae::GTime::GetDeltaTime() const
{
	return m_DeltaTime;
}

const float dae::GTime::GetTimeStep() const
{
	return m_Timestep;
}

const int dae::GTime::GetFrameTime() const
{
	return m_FrameTime;
}

const std::chrono::time_point<std::chrono::steady_clock> dae::GTime::GetLastTimeStamp() const
{
	return m_LastTimestamp;
}