#include "Graphics/OpenGlShader.h"

#include <cassert>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <utility>
#include <glad/gl.h>

#include "Matrix3.h"
#include "Matrix4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

namespace fs = std::filesystem;
using std::fstream;
using std::runtime_error;

namespace Catalyst::Graphics::OpenGL
{
	OpenGlShader::SubShader::~SubShader()
	{
		delete[] m_lastError;
		glDeleteShader(m_handle);
	}

	OpenGlShader::SubShader::SubShader(uint32 stage, string file)
		: m_stage{ stage }, m_handle{ 0 }, m_file{ std::move(file) }, m_lastError{ nullptr } { }

	uint32 OpenGlShader::SubShader::GetStage() const
	{
		return m_stage;
	}

	uint32 OpenGlShader::SubShader::GetHandle() const
	{
		return m_handle;
	}

	string OpenGlShader::SubShader::LoadSource() const
	{
		string source;

		// Attempt to open the shader file for reading
		fstream file;
		file.open(m_file, std::ios::in);
		if (file.is_open())
		{
			// Read the shader line by line
			string line;
			while (std::getline(file, line))
			{
				source += line;
			}
		}

		// Close the file and return the source
		file.close();
		return source;
	}

	void OpenGlShader::SubShader::Create(const string& source)
	{
		assert(m_stage > 0 && m_stage < EShaderStage::ShaderStageCount);

		switch (m_stage)
		{
			case Vertex:
			{
				m_handle = glCreateShader(GL_VERTEX_SHADER);
				break;
			}
			case TessellationEvaluation:
			{
				m_handle = glCreateShader(GL_TESS_EVALUATION_SHADER);
				break;
			}
			case TessellationControl:
			{
				m_handle = glCreateShader(GL_TESS_CONTROL_SHADER);
				break;
			}
			case Geometry:
			{
				m_handle = glCreateShader(GL_GEOMETRY_SHADER);
				break;
			}
			case Fragment:
			{
				m_handle = glCreateShader(GL_FRAGMENT_SHADER);
				break;
			}
			default:
			{
				m_handle = static_cast<uint32>(-1);
				break;
			}
		}

		const char* src = source.c_str();
		glShaderSource(m_handle, 1, &src, nullptr);
		glCompileShader(m_handle);

		int success = GL_TRUE;
		glGetShaderiv(m_handle, GL_LINK_STATUS, &success);
		if (success == GL_FALSE)
		{
			int infoLogLength = 0;
			glGetShaderiv(m_handle, GL_INFO_LOG_LENGTH, &infoLogLength);

			delete[] m_lastError;
			m_lastError = new char[infoLogLength];
			glGetShaderInfoLog(m_handle, infoLogLength, nullptr, m_lastError);
		}
	}

	OpenGlShader::OpenGlShader(const string& path)
		: IShader{ path }, m_program{ 0 }, m_subShaders{ }, m_lastError{ nullptr } { }

	OpenGlShader::~OpenGlShader()
	{
		for (const SubShader* shader : m_subShaders)
		{
			delete shader;
		}

		delete[] m_lastError;
		glDeleteProgram(m_program);
	}

	const char* OpenGlShader::GetLastError() const
	{
		return m_lastError;
	}

	bool OpenGlShader::Load()
	{
		vector<SubShader*> subShaders;

		EShaderStage stage = Vertex;
		for (const string& extension : Extensions())
		{
			if (fs::path path{ Path() + extension }; fs::exists(path))
			{
				SubShader* shader = new SubShader{ stage, path.string() };
				shader->Create(shader->LoadSource());
				subShaders.emplace_back(shader);

				stage = static_cast<EShaderStage>(static_cast<uint8>(stage) + 1);
			}
		}

		for (SubShader* shader : subShaders)
		{
			Attach(shader);
		}

		if (!Link())
		{
			printf_s("%s", m_lastError);
			return false;
		}

		return true;
	}

	void OpenGlShader::Bind(ICommandBuffer* cmd)
	{
		assert(m_program > 0 && "Invalid shader program");
		glUseProgram(m_program);
	}

	void OpenGlShader::Unbind(ICommandBuffer* cmd)
	{
		glUseProgram(0);
	}

	void OpenGlShader::Set(const string& id, float value)
	{
		assert(m_program > 0 && "Program must be built setting uniforms.");

		// Attempt to get the uniform location, if unsuccessful, throw an error
		const int location = GetUniformLocation(id);
		if (location < 0)
		{
			throw runtime_error("Invalid uniform location.");
		}

		// Assign the uniform.
		glUniform1f(location, value);
	}

	void OpenGlShader::Set(const string& id, int value)
	{
		assert(m_program > 0 && "Program must be built setting uniforms.");

		// Attempt to get the uniform location, if unsuccessful, throw an error
		const int location = GetUniformLocation(id);
		if (location < 0)
		{
			throw runtime_error("Invalid uniform location.");
		}

		// Assign the uniform.
		glUniform1i(location, value);
	}

	void OpenGlShader::Set(const string& id, const Vector2& value)
	{
		assert(m_program > 0 && "Program must be built setting uniforms.");

		// Attempt to get the uniform location, if unsuccessful, throw an error
		const int location = GetUniformLocation(id);
		if (location < 0)
		{
			throw runtime_error("Invalid uniform location.");
		}

		// Assign the uniform.
		glUniform2f(location, value.x, value.y);
	}

	void OpenGlShader::Set(const string& id, const Vector3& value)
	{
		assert(m_program > 0 && "Program must be built setting uniforms.");

		// Attempt to get the uniform location, if unsuccessful, throw an error
		const int location = GetUniformLocation(id);
		if (location < 0)
		{
			throw runtime_error("Invalid uniform location.");
		}

		// Assign the uniform.
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGlShader::Set(const string& id, const Vector4& value)
	{
		assert(m_program > 0 && "Program must be built setting uniforms.");

		// Attempt to get the uniform location, if unsuccessful, throw an error
		const int location = GetUniformLocation(id);
		if (location < 0)
		{
			throw runtime_error("Invalid uniform location.");
		}

		// Assign the uniform.
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGlShader::Set(const string& id, const Matrix3& value)
	{
		assert(m_program > 0 && "Program must be built setting uniforms.");

		// Attempt to get the uniform location, if unsuccessful, throw an error
		const int location = GetUniformLocation(id);
		if (location < 0)
		{
			throw runtime_error("Invalid uniform location.");
		}

		// Assign the uniform.
		glUniformMatrix3fv(location, 1, GL_FALSE, &value[0]);
	}

	void OpenGlShader::Set(const string& id, const Matrix4& value)
	{
		assert(m_program > 0 && "Program must be built setting uniforms.");

		// Attempt to get the uniform location, if unsuccessful, throw an error
		const int location = GetUniformLocation(id);
		if (location < 0)
		{
			throw runtime_error("Invalid uniform location.");
		}

		// Assign the uniform.
		glUniformMatrix4fv(location, 1, GL_FALSE, &value[0]);
	}

	void OpenGlShader::Set(const string& id, float* value, int count)
	{
		assert(m_program > 0 && "Program must be built setting uniforms.");

		// Attempt to get the uniform location, if unsuccessful, throw an error
		const int location = GetUniformLocation(id);
		if (location < 0)
		{
			throw runtime_error("Invalid uniform location.");
		}

		// Assign the uniform.
		glUniform1fv(location, count, reinterpret_cast<const GLfloat*>(value));
	}

	void OpenGlShader::Set(const string& id, int* value, int count)
	{
		assert(m_program > 0 && "Program must be built setting uniforms.");

		// Attempt to get the uniform location, if unsuccessful, throw an error
		const int location = GetUniformLocation(id);
		if (location < 0)
		{
			throw runtime_error("Invalid uniform location.");
		}

		// Assign the uniform.
		glUniform1iv(location, count, value);
	}

	void OpenGlShader::Set(const string& id, Vector2* value, int count)
	{
		assert(m_program > 0 && "Program must be built setting uniforms.");

		// Attempt to get the uniform location, if unsuccessful, throw an error
		const int location = GetUniformLocation(id);
		if (location < 0)
		{
			throw runtime_error("Invalid uniform location.");
		}

		// Assign the uniform.
		glUniform2fv(location, count, reinterpret_cast<const GLfloat*>(value));
	}

	void OpenGlShader::Set(const string& id, Vector3* value, int count)
	{
		assert(m_program > 0 && "Program must be built setting uniforms.");

		// Attempt to get the uniform location, if unsuccessful, throw an error
		const int location = GetUniformLocation(id);
		if (location < 0)
		{
			throw runtime_error("Invalid uniform location.");
		}

		// Assign the uniform.
		glUniform3fv(location, count, reinterpret_cast<const GLfloat*>(value));
	}

	void OpenGlShader::Set(const string& id, Vector4* value, int count)
	{
		assert(m_program > 0 && "Program must be built setting uniforms.");

		// Attempt to get the uniform location, if unsuccessful, throw an error
		const int location = GetUniformLocation(id);
		if (location < 0)
		{
			throw runtime_error("Invalid uniform location.");
		}

		// Assign the uniform.
		glUniform4fv(location, count, reinterpret_cast<const GLfloat*>(value));
	}

	void OpenGlShader::Set(const string& id, Matrix3* value, int count)
	{
		assert(m_program > 0 && "Program must be built setting uniforms.");

		// Attempt to get the uniform location, if unsuccessful, throw an error
		const int location = GetUniformLocation(id);
		if (location < 0)
		{
			throw runtime_error("Invalid uniform location.");
		}

		// Assign the uniform.
		glUniformMatrix3fv(location, count, GL_FALSE, reinterpret_cast<const GLfloat*>(value));
	}

	void OpenGlShader::Set(const string& id, Matrix4* value, int count)
	{
		assert(m_program > 0 && "Program must be built setting uniforms.");

		// Attempt to get the uniform location, if unsuccessful, throw an error
		const int location = GetUniformLocation(id);
		if (location < 0)
		{
			throw runtime_error("Invalid uniform location.");
		}

		// Assign the uniform.
		glUniformMatrix4fv(location, count, GL_FALSE, reinterpret_cast<const GLfloat*>(value));
	}

	vector<string> OpenGlShader::Extensions()
	{
		return { "frag", "vert", "geom", "tesseval", "tessctrl", "compute" };
	}

	int OpenGlShader::GetUniformLocation(const string& name) const
	{
		assert(m_program > 0 && "Program must be built before retrieving uniform location.");
		return glGetUniformLocation(m_program, name.c_str());
	}

	void OpenGlShader::Attach(SubShader* shader)
	{
		assert(shader != nullptr);
		m_subShaders[shader->GetStage()] = shader;
	}

	bool OpenGlShader::Link()
	{
		// Create the program and iterate over each sub-shader
		m_program = glCreateProgram();
		for (const SubShader* s : m_subShaders)
		{
			// If this is a valid sub-shader, attach it to the program
			if (s != nullptr)
			{
				glAttachShader(m_program, s->GetHandle());
			}
		}
		glLinkProgram(m_program);

		// Attempt to link all sub shaders into the program
		int success = GL_TRUE;
		glGetProgramiv(m_program, GL_LINK_STATUS, &success);
		if (success == GL_FALSE)
		{
			// Get the length of the error to be printed
			int infoLogLength = 0;
			glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLength);

			// Get the new error message from the GPU
			delete[] m_lastError;
			m_lastError = new char[infoLogLength + 1];
			glGetProgramInfoLog(m_program, infoLogLength, nullptr, m_lastError);
			return false;
		}

		return true;
	}
}
