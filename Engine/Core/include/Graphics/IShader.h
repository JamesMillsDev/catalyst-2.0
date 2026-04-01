#pragma once

#include <string>
#include <vector>

#include "catalyst_export.h"

using std::string;
using std::vector;

namespace Catalyst
{
	namespace Math
	{
		struct Vector2;
		struct Vector3;
		struct Vector4;
		struct Matrix3;
		struct Matrix4;
	}

	using Math::Vector2;
	using Math::Vector3;
	using Math::Vector4;
	using Math::Matrix3;
	using Math::Matrix4;

	namespace Graphics
	{
		/**
		 * A simple interface class that is empty in the base API, but has a custom implementation for each
		 * Render Interface.
		 */
		class ICommandBuffer { };

		class CATALYST_EXPORT IShader
		{
		public:
			explicit IShader(string  path);

			virtual ~IShader();

		public:
			[[nodiscard]] const string& Path() const;

			[[nodiscard]] string Name() const;

			virtual bool Load() = 0;

			virtual void Bind(ICommandBuffer* cmd) = 0;

			virtual void Unbind(ICommandBuffer* cmd) = 0;

			virtual void Set(const string& id, float value) = 0;

			virtual void Set(const string& id, int value) = 0;

			virtual void Set(const string& id, const Vector2& value) = 0;

			virtual void Set(const string& id, const Vector3& value) = 0;

			virtual void Set(const string& id, const Vector4& value) = 0;

			virtual void Set(const string& id, const Matrix3& value) = 0;

			virtual void Set(const string& id, const Matrix4& value) = 0;

			virtual void Set(const string& id, float* value, int count) = 0;

			virtual void Set(const string& id, int* value, int count) = 0;

			virtual void Set(const string& id, Vector2* value, int count) = 0;

			virtual void Set(const string& id, Vector3* value, int count) = 0;

			virtual void Set(const string& id, Vector4* value, int count) = 0;

			virtual void Set(const string& id, Matrix3* value, int count) = 0;

			virtual void Set(const string& id, Matrix4* value, int count) = 0;

		protected:
			virtual vector<string> Extensions() = 0;

		private:
			string m_path;
		};
	}
}
