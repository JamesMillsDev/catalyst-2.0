/*****************************************************************************
 * Light
 * Created by James Mills on 13/04/2026.
 *****************************************************************************/

#include "Graphics/Light.h"

#include "Quaternion.h"
#include "Vector4.h"

using Catalyst::Math::Quat;

namespace Catalyst::Graphics
{
	Light::Light() :
		m_transform{ 1.f }, m_color{ 1.f }, m_intensity{ 1.f }, m_isDirectional{ false }
	{}

	Light::Light(const Vector3& color, const float intensity) :
		m_transform{ 1.f }, m_color{ color }, m_intensity{ intensity }, m_isDirectional{ false }
	{}

	Light::Light(const Vector3& color, const float intensity, const Vector3& direction) :
		m_transform{ Quat::FromToRotation(Vector3{ 0.f, 0.f, 1.f }, direction).ToMat4() },
		m_color{ color }, m_intensity{ intensity }, m_isDirectional{ true }
	{}

	Vector3 Light::TrueColor() const
	{
		return m_color * m_intensity;
	}

	float Light::Intensity() const
	{
		return m_intensity;
	}

	void Light::SetIntensity(const float intensity)
	{
		m_intensity = intensity;
	}

	Vector3 Light::Color() const
	{
		return m_color;
	}

	void Light::SetColor(const Vector3& color)
	{
		m_color = color;
	}

	Vector3 Light::Location() const
	{
		return m_transform.Translation();
	}

	void Light::SetLocation(const Vector3& location)
	{
		m_transform.SetColumn(3, location);
	}

	Vector3 Light::Direction() const
	{
		return Vector3{ m_transform.Column(2) }; // z-column
	}

	void Light::SetDirection(const Vector3& direction)
	{
		const Vector3 translation = m_transform.Translation();

		m_transform = Matrix4::MakeTranslate(translation) * Quat::FromToRotation(Vector3{ 0.f, 0.f, 1.f }, direction).ToMat4();
	}

	bool Light::IsDirectional() const
	{
		return m_isDirectional;
	}

	void Light::SetIsDirectional(const bool isDirectional)
	{
		m_isDirectional = isDirectional;
	}
}
