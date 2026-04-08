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

	Matrix4 FlyCam::View()
	{
		const float thetaR = CatalystMath::Radians(m_theta);
		const float phiR = CatalystMath::Radians(m_phi);

		const Vector3 forward =
		{
			CatalystMath::Cos(phiR) * CatalystMath::Cos(thetaR),
			CatalystMath::Sin(phiR),
			CatalystMath::Cos(phiR) * CatalystMath::Sin(thetaR)
		};

		return Matrix4::MakeLookAt(m_location, m_location + forward, Vector3::UP);
	}

	void FlyCam::Tick()
	{
		InputManagerImpl const* inputManager = IInputManager::Instance<InputManagerImpl>();
		
		const float thetaR = CatalystMath::Radians(m_theta);
		const float phiR = CatalystMath::Radians(m_phi);

		const Vector3 forward =
		{
			CatalystMath::Cos(phiR) * CatalystMath::Cos(thetaR),
			CatalystMath::Sin(phiR),
			CatalystMath::Cos(phiR) * CatalystMath::Sin(thetaR)
		};

		const Vector3 right
		{
			-CatalystMath::Sin(thetaR),
			0,
			CatalystMath::Cos(thetaR)
		};

		if (inputManager->IsKeyDown(W))
		{
			m_location += forward * m_moveSpeed * GameTime::DeltaTime();
		}

		if (inputManager->IsKeyDown(S))
		{
			m_location -= forward * m_moveSpeed * GameTime::DeltaTime();
		}

		if (inputManager->IsKeyDown(D))
		{
			m_location += right * m_moveSpeed * GameTime::DeltaTime();
		}

		if (inputManager->IsKeyDown(A))
		{
			m_location -= right * m_moveSpeed * GameTime::DeltaTime();
		}

		if (inputManager->IsKeyDown(E))
		{
			m_location += Vector3::UP * m_moveSpeed * GameTime::DeltaTime();
		}

		if (inputManager->IsKeyDown(Q))
		{
			m_location -= Vector3::UP * m_moveSpeed * GameTime::DeltaTime();
		}

		const Vector2 mousePos = inputManager->GetMouseLocation();

		if (inputManager->IsMouseButtonDown(MouseButtonRight))
		{
			m_theta += m_turnSpeed * (mousePos.x - m_lastMouse.x) * GameTime::DeltaTime();
			m_phi   += m_turnSpeed * (mousePos.y - m_lastMouse.y) * GameTime::DeltaTime();
		}

		m_lastMouse = mousePos;
	}
}
