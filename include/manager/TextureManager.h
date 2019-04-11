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

		int										Initialize();
		int										Destroy();

		TexturePtr								CreateTexture(const char* textureFilename);
		TexturePtr								CreateTexture(const char* hasname, unsigned int width, unsigned int height, int internalFormat, int format, int type, void* data);

	private:
		
		std::map<std::string, TexturePtr>		m_TextureMap; // note: we don't delete textures yet
	};

	typedef std::shared_ptr<TextureManager>		TextureManagerPtr;
}