#pragma once
#include "defines.h"

#include "rendering/Shader_OpenGL.h"

namespace GameEngine
{
	class ShaderManager
	{
	public:

											ShaderManager();
											~ShaderManager();

		int									Initialize();
		int									Destroy();

		ShaderPtr							CreateShader(const char* vertexFilename, const char* fragmentFilename, const char* defines = NULL);

	private:

		std::map<std::string, ShaderPtr>	m_ShaderMap;
	};

	typedef std::shared_ptr<ShaderManager>	ShaderManagerPtr;
}