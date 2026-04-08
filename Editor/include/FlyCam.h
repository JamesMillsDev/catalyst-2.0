/*****************************************************************************
 * FlyCam
 * Created by James Mills on 7/04/2026.
 *****************************************************************************/

#pragma once

#include "Vector2.h"
#include "Vector3.h"

#include "Graphics/Camera.h"

using Catalyst::Math::Vector2;
using Catalyst::Math::Vector3;

namespace Catalyst::Editor
{
	using Graphics::Camera;

	class FlyCam : public Camera
	{
	public:
		FlyCam();

	public:
		[[nodiscard]] virtual Matrix4 View() override;

		virtual void Tick() override;

	protected:
		float m_theta;
		float m_phi;

		float m_turnSpeed;
		float m_moveSpeed;

		Vector3 m_location;
		Vector2 m_lastMouse;
	};
}
