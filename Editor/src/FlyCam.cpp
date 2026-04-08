/*****************************************************************************
 * FlyCam
 * Created by James Mills on 7/04/2026.
 *****************************************************************************/

#include "FlyCam.h"

#include "CatalystMath.h"
#include "GameTime.h"
#include "IInputManager.h"
#include "Implementations.h"
#include "Vector3.h"

using Catalyst::Math::CatalystMath;

namespace Catalyst::Editor
{
	FlyCam::FlyCam()
		: m_theta{ 0 }, m_phi{ 0 }, m_turnSpeed{ CatalystMath::Radians(180.f) },
		  m_moveSpeed{ 5.f }, m_lastMouse{ 0.f }
	{
		m_view = Matrix4::MakeTransform({ 0.f, 0.f, -10.f }, { 0.f }, { 1.f });
	}

	void FlyCam::Tick()
	{
		InputManagerImpl const* inputManager = IInputManager::Instance<InputManagerImpl>();

		if (inputManager->IsKeyDown(W))
		{
			m_view *= Matrix4::MakeTranslate(0.f, 0.f, 1.f * m_moveSpeed * GameTime::DeltaTime());
		}

		if (inputManager->IsKeyDown(S))
		{
			m_view *= Matrix4::MakeTranslate(0.f, 0.f, -1.f * m_moveSpeed * GameTime::DeltaTime());
		}

		if (inputManager->IsKeyDown(D))
		{
			m_view *= Matrix4::MakeTranslate(-1.f * m_moveSpeed * GameTime::DeltaTime(), 0.f, 0.f);
		}

		if (inputManager->IsKeyDown(A))
		{
			m_view *= Matrix4::MakeTranslate(1.f * m_moveSpeed * GameTime::DeltaTime(), 0.f, 0.f);
		}

		if (inputManager->IsKeyDown(E))
		{
			m_view *= Matrix4::MakeTranslate(0.f, -1.f * m_moveSpeed * GameTime::DeltaTime(), 0.f);
		}

		if (inputManager->IsKeyDown(Q))
		{
			m_view *= Matrix4::MakeTranslate(0.f, 1.f * m_moveSpeed * GameTime::DeltaTime(), 0.f);
		}

		const Vector2 mousePos = inputManager->GetMouseLocation();

		if (inputManager->IsMouseButtonDown(MouseButtonRight))
		{
			m_theta += m_turnSpeed * (mousePos.x - m_lastMouse.x) * GameTime::DeltaTime();
			m_phi   += m_turnSpeed * (mousePos.y - m_lastMouse.y) * GameTime::DeltaTime();

			m_view = Matrix4::MakeTranslate(m_view.Translation()) * Matrix4::MakeRotate({ m_phi, m_theta, 0.f });
		}

		m_lastMouse = mousePos;
	}
}
