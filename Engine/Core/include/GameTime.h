/*****************************************************************************
 * GameTime
 * Created by James Mills on 5/04/2026.
 *****************************************************************************/

#pragma once

#include <chrono>

#include "catalyst_export.h"

#include "Utility/Typedefs.h"

using std::chrono::steady_clock;

namespace Catalyst
{
	class CATALYST_EXPORT GameTime
	{
	public:
		friend class Application;

	public:
		static float DeltaTime();
		static float AppTime();
		static uint32 FPS();

	private:
		static steady_clock::time_point m_currTime;
		static steady_clock::time_point m_prevTime;

		static steady_clock::time_point m_initialTime;

		static float m_deltaTime;
		static uint32 m_frames;
		static float m_fpsInterval;
		static uint32 m_fps;

	private:
		static void Init();
		static void Tick();
	};
}