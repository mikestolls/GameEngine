#pragma once

#include "defines.h"

#include "rendering/Texture_OpenGL.h"

namespace GameEngine
{
	class TextureManager
	{
	public:

												TextureManager();
												~TextureManager();

		TexturePtr								CreateTexture(const char* textureFilename);
		TexturePtr								CreateTexture(const char* hasname, unsigned int width, unsigned int height, int internalFormat, int format, int type, void* data);

	private:
		
		std::map<std::string, TexturePtr>		m_TextureMap;
	};

	typedef std::shared_ptr<TextureManager>		TextureManagerPtr;
}