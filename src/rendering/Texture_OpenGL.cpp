#include "rendering/Texture_OpenGL.h"

#include "defines.h"

namespace GameEngine
{
	Texture_OpenGL::Texture_OpenGL()
	{
		m_TextureId = GL_INVALID_INDEX;
	}

	Texture_OpenGL::Texture_OpenGL(unsigned int width, unsigned int height, int internalFormat, int format, int type, void* data)
	{
		glGenTextures(1, &m_TextureId);
		glBindTexture(GL_TEXTURE_2D, m_TextureId);

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture_OpenGL::Texture_OpenGL(const char* filename)
	{
		m_Filename = filename;
		m_TextureId = GL_INVALID_INDEX;

		ReloadTexture();
	}

	Texture_OpenGL::~Texture_OpenGL()
	{
		if (m_TextureId != GL_INVALID_INDEX)
		{
			glDeleteTextures(1, &m_TextureId);
		}
	}

	void Texture_OpenGL::ReloadTexture()
	{
		if (m_Filename.size() == 0)
		{
			return;
		}

		if (m_TextureId != GL_INVALID_INDEX)
		{
			glDeleteTextures(1, &m_TextureId);
		}

		/*glGenTextures(1, &m_TextureId);
		glBindTexture(GL_TEXTURE_2D, m_TextureId);

		int width = 0;
		int height = 0;
		unsigned char* image = SOIL_load_image(m_Filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

		GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

		glBindTexture(GL_TEXTURE_2D, 0);
		*/
	}
}