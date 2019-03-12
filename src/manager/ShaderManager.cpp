#include "manager/ShaderManager.h"

namespace GameEngine
{
	ShaderManager::ShaderManager()
	{

	}

	ShaderManager::~ShaderManager()
	{

	}

	int ShaderManager::Initialize()
	{
		return 0;
	}

	int ShaderManager::Destroy()
	{
		return 0;
	}

	ShaderPtr ShaderManager::CreateShader(const char* vertexFilename, const char* fragmentFilename, const char* defines)
	{
		std::string key = vertexFilename;
		key.append(fragmentFilename);

		auto itr = m_ShaderMap.find(key);

		ShaderPtr shader;
		if (itr == m_ShaderMap.end())
		{
			shader = ShaderPtr(new Shader_OpenGL(vertexFilename, fragmentFilename, defines));
			m_ShaderMap[key] = shader;
		}
		else
		{
			shader = itr->second;
		}

		return shader;
	}
}