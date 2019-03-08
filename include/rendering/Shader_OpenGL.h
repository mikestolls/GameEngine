#pragma once

#include "defines.h"

namespace GameEngine
{
	enum UniformType
	{
		Int = 0,
		Float,
		Vec2,
		Vec3,
		Vec4,
		Mat3,
		Mat4
	};

	struct ShaderUniform
	{
		UniformType type;
		std::string name;

		int valueInt;
		float valueFloat;
		glm::vec2 valueVec2;
		glm::vec3 valueVec3;
		glm::vec4 valueVec4;
		glm::mat3 valueMat3;
		glm::mat4 valueMat4;
	};

	class IShader
	{
	public:
												IShader() { }
		virtual									~IShader() { }

		virtual void							SetActive() = 0;

		// these methods apply on teh fly
		virtual bool							SetUniformInt1(const char* name, int value) = 0;
		virtual bool							SetUniformFloat1(const char* name, float value) = 0;

		virtual bool							SetUniformVec2(const char* name, glm::vec2 value) = 0;
		virtual bool							SetUniformVec3(const char* name, glm::vec3 value) = 0;
		virtual bool							SetUniformVec4(const char* name, glm::vec4 value) = 0;

		virtual bool							SetUniformMat3(const char* name, glm::mat3 value) = 0;
		virtual bool							SetUniformMat4(const char* name, glm::mat4 value) = 0;

	protected:

		virtual bool							GetUniformLocation(const char* uniform, unsigned int& location) = 0;

		std::string								m_ShaderDefinesStr;
		std::string								m_VertexFilename;
		std::string								m_FragmentFilename;

		std::map<std::string, unsigned int>		m_UniformIds;
	};

	typedef std::shared_ptr<IShader>			ShaderPtr;

	class Shader_OpenGL : public IShader
	{
	public:

												Shader_OpenGL(const char* vertexFilename, const char* fragmentFilename, const char* defines = NULL);
												~Shader_OpenGL();

		void									SetActive();

		// these methods apply on teh fly
		bool									SetUniformInt1(const char* name, int value);
		bool									SetUniformFloat1(const char* name, float value);

		bool									SetUniformVec2(const char* name, glm::vec2 value);
		bool									SetUniformVec3(const char* name, glm::vec3 value);
		bool									SetUniformVec4(const char* name, glm::vec4 value);

		bool									SetUniformMat3(const char* name, glm::mat3 value);
		bool									SetUniformMat4(const char* name, glm::mat4 value);

		// get uniform location from shader
		bool									GetUniformLocation(const char* uniform, unsigned int& location);

	private:

		bool									MapUniformId(const char* uniform);
		void									Recompile(const char* defines = NULL);
		std::string								FilterShaderSource(std::string str, std::string removeStr);

		unsigned int							m_ProgramId;
	};
}