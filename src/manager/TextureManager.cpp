#include "manager/TextureManager.h"

namespace GameEngine
{
	TextureManager::TextureManager()
	{

	}

	TextureManager::~TextureManager()
	{

	}

	TexturePtr TextureManager::CreateTexture(const char* textureFilename)
	{
		auto itr = m_TextureMap.find(textureFilename);

		TexturePtr texture;
		if (itr == m_TextureMap.end())
		{
			texture = TexturePtr(new Texture_OpenGL(textureFilename));
			m_TextureMap[textureFilename] = texture;
		}
		else
		{
			texture = itr->second;
		}

		return texture;
	}

	TexturePtr TextureManager::CreateTexture(const char* hasname, unsigned int width, unsigned int height, int internalFormat, int format, int type, void* data)
	{
		auto itr = m_TextureMap.find(hasname);

		TexturePtr texture;
		if (itr == m_TextureMap.end())
		{
			texture = TexturePtr(new Texture_OpenGL(width, height, internalFormat, format, type, data));
			m_TextureMap[hasname] = texture;
		}
		else
		{
			texture = itr->second;
		}

		return texture;
	}
}