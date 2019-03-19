#include "driver/Driver_OpenGL.h"

#include <GL/gl3w.h>

namespace GameEngine
{
	Driver_OpenGL::Driver_OpenGL()
		: IDriver()
	{

	}

	Driver_OpenGL::~Driver_OpenGL()
	{

	}

	int Driver_OpenGL::Initialize()
	{
		return 0;
	}

	int Driver_OpenGL::Destroy()
	{
		return 0;
	}

	int Driver_OpenGL::PreUpdate()
	{
		return 0;
	}

	int Driver_OpenGL::PostUpdate()
	{
		glViewport(m_ViewportRect.a.x, m_ViewportRect.a.y, m_ViewportRect.b.x, m_ViewportRect.b.y);

		return 0;
	}

	void Driver_OpenGL::SetClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void Driver_OpenGL::Clear(DRIVER_CLEAR clear)
	{
		GLbitfield bitfield = 0x0;

		if ((clear & CLEAR_COLOR) > 0x0)
		{
			bitfield |= GL_COLOR_BUFFER_BIT;
		}

		if ((clear & CLEAR_DEPTH) > 0x0)
		{
			bitfield |= GL_DEPTH_BUFFER_BIT;
		}


		if ((clear & CLEAR_STENCIL) > 0x0)
		{
			bitfield |= GL_STENCIL_BUFFER_BIT;
		}

		glClear(bitfield);
	}
}