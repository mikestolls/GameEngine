#include "rendering/Shader_OpenGL.h"

namespace GameEngine
{
	Shader_OpenGL::Shader_OpenGL(const char* vertexFilename, const char* fragmentFilename, const char* defines)
		: IShader()
	{
		std::string strDefines = "\n";

		if (defines != NULL)
		{
			strDefines.append(defines);
			strDefines.append("\n");
		}

		m_ShaderDefinesStr = strDefines;
		m_VertexFilename = vertexFilename;
		m_FragmentFilename = fragmentFilename;
		m_ProgramId = GL_INVALID_INDEX;

		Recompile();
	}

	Shader_OpenGL::~Shader_OpenGL()
	{
		glDeleteProgram(m_ProgramId);
	}

	void Shader_OpenGL::SetActive()
	{
		glUseProgram(m_ProgramId);
	}

	bool Shader_OpenGL::SetUniformInt1(const char* name, int value)
	{
		unsigned int loc = 0;

		if (GetUniformLocation(name, loc))
		{
			glUniform1i(loc, value);
			return true;
		}

		return false;
	}

	bool Shader_OpenGL::SetUniformFloat1(const char* name, float value)
	{
		unsigned int loc = 0;

		if (GetUniformLocation(name, loc))
		{
			glUniform1f(loc, value);
			return true;
		}

		return false;
	}

	bool Shader_OpenGL::SetUniformVec2(const char* name, glm::vec2 value)
	{
		unsigned int loc = 0;

		if (GetUniformLocation(name, loc))
		{
			glUniform2f(loc, value.x, value.y);
			return true;
		}

		return false;
	}

	bool Shader_OpenGL::SetUniformVec2(const char* name, float* value)
	{
		unsigned int loc = 0;

		if (GetUniformLocation(name, loc))
		{
			glUniform2f(loc, value[0], value[1]);
			return true;
		}

		return false;
	}

	bool Shader_OpenGL::SetUniformVec3(const char* name, glm::vec3 value)
	{
		unsigned int loc = 0;

		if (GetUniformLocation(name, loc))
		{
			glUniform3f(loc, value.x, value.y, value.z);
			return true;
		}

		return false;
	}

	bool Shader_OpenGL::SetUniformVec3(const char* name, float* value)
	{
		unsigned int loc = 0;

		if (GetUniformLocation(name, loc))
		{
			glUniform3f(loc, value[0], value[1], value[2]);
			return true;
		}

		return false;
	}

	bool Shader_OpenGL::SetUniformVec4(const char* name, glm::vec4 value)
	{
		unsigned int loc = 0;

		if (GetUniformLocation(name, loc))
		{
			glUniform4f(loc, value.x, value.y, value.z, value.w);
			return true;
		}

		return false;
	}

	bool Shader_OpenGL::SetUniformVec4(const char* name, float* value)
	{
		unsigned int loc = 0;

		if (GetUniformLocation(name, loc))
		{
			glUniform4f(loc, value[0], value[1], value[2], value[3]);
			return true;
		}

		return false;
	}

	bool Shader_OpenGL::SetUniformMat3(const char* name, glm::mat3 value)
	{
		unsigned int loc = 0;

		if (GetUniformLocation(name, loc))
		{
			glUniformMatrix3fv(loc, 1, GL_FALSE, &value[0][0]);
			return true;
		}

		return false;
	}

	bool Shader_OpenGL::SetUniformMat3(const char* name, float* value)
	{
		unsigned int loc = 0;

		if (GetUniformLocation(name, loc))
		{
			glUniformMatrix3fv(loc, 1, GL_FALSE, value);
			return true;
		}

		return false;
	}

	bool Shader_OpenGL::SetUniformMat4(const char* name, glm::mat4 value)
	{
		unsigned int loc = 0;

		if (GetUniformLocation(name, loc))
		{
			glUniformMatrix4fv(loc, 1, GL_FALSE, &value[0][0]);
			return true;
		}

		return false;
	}

	bool Shader_OpenGL::SetUniformMat4(const char* name, float* value)
	{
		unsigned int loc = 0;

		if (GetUniformLocation(name, loc))
		{
			glUniformMatrix4fv(loc, 1, GL_FALSE, value);
			return true;
		}

		return false;
	}

	bool Shader_OpenGL::GetUniformLocation(const char* name, unsigned int& location)
	{
		glUseProgram(m_ProgramId);

		auto itr = m_UniformIds.find(name);

		if (itr == m_UniformIds.end())
		{
			// attempt to map
			if (MapUniformId(name))
			{
				return GetUniformLocation(name, location);
			}

			return false;
		}

		location = itr->second;
		return true;
	}

	bool Shader_OpenGL::MapUniformId(const char* name)
	{
		int ret = glGetUniformLocation(m_ProgramId, name);

		if (ret == -1)
		{
			return false;
		}

		m_UniformIds[name] = ret;
		return true;
	}

	void Shader_OpenGL::Recompile(const char* defines)
	{
		if (m_ProgramId != GL_INVALID_INDEX)
		{
			glDeleteProgram(m_ProgramId);
		}


		if (defines != NULL)
		{
			std::string strDefines = "\n";
			strDefines.append(defines);
			strDefines.append("\n");
			m_ShaderDefinesStr = strDefines;
		}

		// Create the shaders
		GLuint vertShaderId = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragShaderId = glCreateShader(GL_FRAGMENT_SHADER);

		std::string vertShaderCode;
		std::ifstream inStream(m_VertexFilename.c_str(), std::ios::in);
		if (inStream.is_open())
		{
			std::string line = "";
			while (getline(inStream, line))
			{
				line = FilterShaderSource(line, "lowp");
				line = FilterShaderSource(line, "mediump");
				line = FilterShaderSource(line, "highp");

				vertShaderCode += "\n" + line;

				if (strstr(line.c_str(), "#version") != NULL)
				{
					vertShaderCode += m_ShaderDefinesStr;
				}
			}
			inStream.close();
		}
		else
		{
			printf("Error opening vertex shader\n");
			return;
		}

		// Read the Fragment Shader code from the file
		std::string fragShaderCode;
		inStream.open(m_FragmentFilename.c_str(), std::ios::in);
		if (inStream.is_open())
		{
			std::string line = "";
			while (getline(inStream, line))
			{
				line = FilterShaderSource(line, "lowp");
				line = FilterShaderSource(line, "mediump");
				line = FilterShaderSource(line, "highp");

				fragShaderCode += "\n" + line;

				if (strstr(line.c_str(), "#version") != NULL)
				{
					fragShaderCode += m_ShaderDefinesStr;
				}
			}
			inStream.close();
		}
		else
		{
			printf("Error opening fragment shader\n");
			return;
		}

		GLint res = GL_FALSE;
		int logLength;

		// Compile Vertex Shader_OpenGL
		char const* vertSourcePtr = vertShaderCode.c_str();
		glShaderSource(vertShaderId, 1, &vertSourcePtr, NULL);
		glCompileShader(vertShaderId);

		// Check Vertex Shader_OpenGL
		glGetShaderiv(vertShaderId, GL_COMPILE_STATUS, &res);
		glGetShaderiv(vertShaderId, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength > 0)
		{
			std::vector<char> infoMsg(logLength + 1);
			glGetShaderInfoLog(vertShaderId, logLength, NULL, &infoMsg[0]);
			printf("%s\n", &infoMsg[0]);
		}

		// Compile Fragment Shader_OpenGL
		char const* fragSourcePtr = fragShaderCode.c_str();
		glShaderSource(fragShaderId, 1, &fragSourcePtr, NULL);
		glCompileShader(fragShaderId);

		// Check Fragment Shader_OpenGL
		glGetShaderiv(fragShaderId, GL_COMPILE_STATUS, &res);
		glGetShaderiv(fragShaderId, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength > 0)
		{
			std::vector<char> infoMsg(logLength + 1);
			glGetShaderInfoLog(fragShaderId, logLength, NULL, &infoMsg[0]);
			printf("%s\n", &infoMsg[0]);
		}

		// Link the program
		printf("Linking program\n");
		m_ProgramId = glCreateProgram();
		glAttachShader(m_ProgramId, vertShaderId);
		glAttachShader(m_ProgramId, fragShaderId);
		glLinkProgram(m_ProgramId);

		// Check the program
		glGetProgramiv(m_ProgramId, GL_LINK_STATUS, &res);
		glGetProgramiv(m_ProgramId, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength > 0)
		{
			std::vector<char> infoMsg(logLength + 1);
			glGetProgramInfoLog(m_ProgramId, logLength, NULL, &infoMsg[0]);
			printf("%s\n", &infoMsg[0]);
		}

		glDetachShader(m_ProgramId, vertShaderId);
		glDetachShader(m_ProgramId, fragShaderId);

		glDeleteShader(vertShaderId);
		glDeleteShader(fragShaderId);

		m_UniformIds.clear();
	}

	std::string Shader_OpenGL::FilterShaderSource(std::string str, std::string removeStr)
	{
		std::string::size_type index = std::string::npos;
		do
		{
			index = str.find(removeStr);

			if (index != std::string::npos)
			{
				str.erase(index, removeStr.length());
			}
		} while (index != std::string::npos);

		return str;
	}
}