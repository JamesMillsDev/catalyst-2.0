#pragma once

#include <Matrix4.h>

#include "catalyst_export.h"

namespace Catalyst
{
	using Math::Matrix4;

	namespace Graphics
	{
		class CATALYST_EXPORT Camera
		{
		public:
			[[nodiscard]] static float Aspect();

		public:
			Camera();
			Camera(float fovAngle, float nearPlane, float farPlane);

			virtual ~Camera();

		public:
			Matrix4& View();
			[[nodiscard]] float Fov() const;

			Matrix4 ProjectTransform(const Matrix4& transform) const;
			Matrix4 Projection() const;

			void SetFovAngle(float fovAngle);
			[[nodiscard]] float GetFovAngle() const;

			void SetNearPlane(float nearPlane);
			[[nodiscard]] float GetNearPlane() const;

			void SetFarPlane(float farPlane);
			[[nodiscard]] float GetFarPlane() const;

			virtual void Tick();

		protected:
			Matrix4 m_view;
			Matrix4 m_projection;

			float m_fovAngle;
			float m_nearPlane;
			float m_farPlane;

		};
	}
}
