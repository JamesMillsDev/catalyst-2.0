#include "Graphics/Camera.h"

#include <CatalystMath.h>

#include "Application.h"
#include "IWindow.h"

using Catalyst::Application;
using Catalyst::IWindow;
using Catalyst::Math::CatalystMath;

namespace Catalyst::Graphics
{
	float Camera::Aspect()
	{
		IWindow const* window = Application::Instance()->GetWindow();

		return window->Width() / window->Height();
	}

	Camera::Camera()
		: Camera{ 60.f, .1f, 1000.f } { }

	Camera::Camera(const float fovAngle, const float nearPlane, const float farPlane)
		: m_view{ 1.f }, m_projection{ 1.f }, m_fovAngle{ fovAngle }, m_nearPlane{ nearPlane },
		  m_farPlane{ farPlane } { }

	Camera::~Camera() = default;

	Matrix4& Camera::View()
	{
		return m_view;
	}

	float Camera::Fov() const
	{
		return CatalystMath::Radians(m_fovAngle);
	}

	Matrix4 Camera::ProjectTransform(const Matrix4& transform) const
	{
		return Projection() * transform;
	}

	Matrix4 Camera::Projection() const
	{
		return Matrix4::MakePerspective(Fov(), Aspect(), m_nearPlane, m_farPlane);
	}

	void Camera::SetFovAngle(const float fovAngle)
	{
		m_fovAngle = fovAngle;
	}

	float Camera::GetFovAngle() const
	{
		return m_fovAngle;
	}

	void Camera::SetNearPlane(const float nearPlane)
	{
		m_nearPlane = nearPlane;
	}

	float Camera::GetNearPlane() const
	{
		return m_nearPlane;
	}

	void Camera::SetFarPlane(const float farPlane)
	{
		m_farPlane = farPlane;
	}

	float Camera::GetFarPlane() const
	{
		return m_farPlane;
	}

	void Camera::Tick()
	{
	}
}
