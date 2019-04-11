#include "rendering/FrameBuffer_OpenGL.h"
#include "Engine.h"

#include "defines.h"

namespace GameEngine
{
	FrameBuffer_OpenGL::FrameBuffer_OpenGL(unsigned int width, unsigned int height, unsigned int type)
	{
		m_FrameBufferId = 0;
		m_DepthRenderBufferId = 0;

		glGenFramebuffers(1, &m_FrameBufferId);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferId);

		m_Width = width;
		m_Height = height;

		m_ColorTexture.resize(4);

		// create color texture
		if ((type & FRAMEBUFFER_COLORTEXTURE0) != 0)
		{
			TexturePtr texture = Engine::GetInstance()->GetTextureMgr()->CreateTexture("", width, height, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, 0);
			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture->GetTextureId(), 0);
			m_ColorTexture[0] = texture;
		}

		if ((type & FRAMEBUFFER_COLORTEXTURE1) != 0)
		{
			TexturePtr texture = Engine::GetInstance()->GetTextureMgr()->CreateTexture("", width, height, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, 0);
			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, texture->GetTextureId(), 0);
			m_ColorTexture[1] = texture;
		}

		if ((type & FRAMEBUFFER_COLORTEXTURE2) != 0)
		{
			TexturePtr texture = Engine::GetInstance()->GetTextureMgr()->CreateTexture("", width, height, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, 0);
			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, texture->GetTextureId(), 0);
			m_ColorTexture[2] = texture;
		}

		if ((type & FRAMEBUFFER_COLORTEXTURE3) != 0)
		{
			TexturePtr texture = Engine::GetInstance()->GetTextureMgr()->CreateTexture("", width, height, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, 0);
			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, texture->GetTextureId(), 0);
			m_ColorTexture[3] = texture;
		}

		// create depth buffer
		if ((type & FRAMEBUFFER_DEPTHBUFFER) != 0)
		{
			glGenRenderbuffers(1, &m_DepthRenderBufferId);
			glBindRenderbuffer(GL_RENDERBUFFER, m_DepthRenderBufferId);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthRenderBufferId);
		}

		// create depth texture
		if ((type & FRAMEBUFFER_DEPTHTEXTURE) != 0)
		{
			m_DepthTexture = Engine::GetInstance()->GetTextureMgr()->CreateTexture("", width, height, GL_DEPTH_COMPONENT32, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
			glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_DepthTexture->GetTextureId(), 0);
		}

		GLuint attachments[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
		glDrawBuffers(4, attachments);

		int ret = 0;
		if (ret = glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			printf("Error creating Frame Buffer\n");
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	FrameBuffer_OpenGL::~FrameBuffer_OpenGL()
	{
		for (auto texture : m_ColorTexture)
		{
			texture = nullptr;
		}

		m_DepthTexture = nullptr;

		if (m_DepthRenderBufferId != 0)
		{
			glDeleteRenderbuffers(1, &m_DepthRenderBufferId);
		}
	}

	void FrameBuffer_OpenGL::Push()
	{
		// Render to our framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferId);
		glViewport(0, 0, m_Width, m_Height);
	}

	void FrameBuffer_OpenGL::Pop()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}