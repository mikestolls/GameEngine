#pragma once

#include "defines.h"

namespace GameEngine
{
	class ITexture
	{
	public:
											ITexture() { }
		virtual								~ITexture() { }

		inline unsigned int					GetTextureId() { return m_TextureId; }

		virtual void						ReloadTexture() = 0;

	protected:

		std::string							m_Filename;

		unsigned int						m_TextureId;
	};

	typedef std::shared_ptr<ITexture>		TexturePtr;

	class Texture_OpenGL : public ITexture
	{
	public:
											Texture_OpenGL();
											Texture_OpenGL(unsigned int width, unsigned int height, int internalFormat, int format, int type, void* data);
											Texture_OpenGL(const char* filename);
											~Texture_OpenGL();

		virtual void						ReloadTexture();

	};
}