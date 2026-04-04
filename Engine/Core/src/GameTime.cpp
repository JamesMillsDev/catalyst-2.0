/*****************************************************************************
 * GameTime
 * Created by James Mills on 5/04/2026.
 *****************************************************************************/

#include "GameTime.h"

namespace Catalyst
{
	steady_clock::time_point GameTime::m_currTime;
	steady_clock::time_point GameTime::m_prevTime;

	steady_clock::time_point GameTime::m_initialTime;

	float GameTime::m_deltaTime;
	uint32 GameTime::m_frames;
	float GameTime::m_fpsInterval;
	uint32 GameTime::m_fps;

	float GameTime::DeltaTime()
	{
		return m_deltaTime;
	}

	float GameTime::AppTime()
	{
		return std::chrono::duration<float>(m_currTime - m_initialTime).count();
	}

	uint32 GameTime::FPS()
	{
		return m_fps;
	}

	void GameTime::Init()
	{
		m_initialTime = steady_clock::now();
		m_prevTime = steady_clock::now();
		m_currTime = m_initialTime;
	}

	void GameTime::Tick()
	{
		m_currTime = steady_clock::now();
		m_deltaTime = std::chrono::duration<float>(m_currTime - m_prevTime).count();
		if (m_deltaTime > .1f)
		{
			m_deltaTime = .1f;
		}

		m_prevTime = m_currTime;

		m_frames++;
		m_fpsInterval += m_deltaTime;
		if (m_fpsInterval >= 1.f)
		{
			m_fps = m_frames;;
			m_frames = 0;
			m_fpsInterval -= 1.f;
		}
	}
}
