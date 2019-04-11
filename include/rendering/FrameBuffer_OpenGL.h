#pragma once

#include "defines.h"

#include "rendering/Texture_OpenGL.h"

namespace GameEngine
{
	class IFrameBuffer
	{
	public:
		enum
		{
			FRAMEBUFFER_COLORTEXTURE0 = 0x01,
			FRAMEBUFFER_COLORTEXTURE1 = 0x02,
			FRAMEBUFFER_COLORTEXTURE2 = 0x04,
			FRAMEBUFFER_COLORTEXTURE3 = 0x08,
			FRAMEBUFFER_DEPTHBUFFER = 0x10,
			FRAMEBUFFER_DEPTHTEXTURE = 0x20,
		};

											IFrameBuffer() { }
		virtual								~IFrameBuffer() { }

		virtual void						Push() = 0;
		virtual void						Pop() = 0;
	};

	typedef std::shared_ptr<IFrameBuffer>	FrameBufferPtr;

	class FrameBuffer_OpenGL : public IFrameBuffer
	{
	public:
											FrameBuffer_OpenGL(unsigned int width, unsigned int height, unsigned int type);
											~FrameBuffer_OpenGL();

		void								Push();
		void								Pop();

		inline unsigned int					GetFrameBufferId() { return m_FrameBufferId; }

		inline unsigned int					GetColorTextureId(unsigned int index) { return ((m_ColorTexture.size() < index || m_ColorTexture[index] == NULL) ? NULL : m_ColorTexture[index]->GetTextureId()); }
		inline unsigned int					GetDepthBufferId() { return m_DepthRenderBufferId; }
		inline unsigned int					GetDepthTextureId() { return (m_DepthTexture ? m_DepthTexture->GetTextureId() : 0); }

	private:

		unsigned int						m_FrameBufferId;
		unsigned int						m_DepthRenderBufferId;

		std::vector<TexturePtr>				m_ColorTexture;
		TexturePtr							m_DepthTexture;

		unsigned int						m_Width;
		unsigned int						m_Height;
	};
}