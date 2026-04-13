#pragma once

#include "catalyst_opengl_export.h"
#include "Graphics/IShader.h"
#include "Utility/Typedefs.h"

namespace Catalyst::Graphics::OpenGL
{
	class CATALYSTOPENGL_EXPORT OpenGlShader : public IShader
	{
	private:
		enum EShaderStage : uint8
		{
			Undefined = 0,
			Fragment,
			Vertex,
			Geometry,
			TessellationEvaluation,
			TessellationControl,
			ShaderStageCount
		};

		class CATALYSTOPENGL_EXPORT SubShader
		{
			friend class OpenGlShader;

		public:
			~SubShader();

		private:
			uint32 m_stage;
			uint32 m_handle;
			string m_file;
			char* m_lastError;

		private:
			explicit SubShader(uint32 stage, string  file);

		private:
			[[nodiscard]] uint32 GetStage() const;

			[[nodiscard]] uint32 GetHandle() const;

			string LoadSource() const;

			void Create(const string& source);
		};

	public:
		explicit OpenGlShader(const string& path);

		virtual ~OpenGlShader() override;

	public:
		[[nodiscard]] const char* GetLastError() const;

		virtual bool Load() override;

		virtual void Bind(ICommandBuffer* cmd) override;

		virtual void Unbind(ICommandBuffer* cmd) override;

		virtual void Set(const string& id, float value) override;

		virtual void Set(const string& id, int value) override;

		virtual void Set(const string& id, const Vector2& value) override;

		virtual void Set(const string& id, const Vector3& value) override;

		virtual void Set(const string& id, const Vector4& value) override;

		virtual void Set(const string& id, const Matrix3& value) override;

		virtual void Set(const string& id, const Matrix4& value) override;

		virtual void Set(const string& id, float* value, int count) override;

		virtual void Set(const string& id, int* value, int count) override;

		virtual void Set(const string& id, Vector2* value, int count) override;

		virtual void Set(const string& id, Vector3* value, int count) override;

		virtual void Set(const string& id, Vector4* value, int count) override;

		virtual void Set(const string& id, Matrix3* value, int count) override;

		virtual void Set(const string& id, Matrix4* value, int count) override;

		virtual void Set(const string& id, ITexture* value, int index) override;

	protected:
		virtual vector<string> Extensions() override;

	private:
		uint32 m_program;
		SubShader* m_subShaders[ShaderStageCount];
		char* m_lastError;

	private:
		int GetUniformLocation(const string& name) const;

		void Attach(SubShader* shader);

		bool Link();
	};
}
