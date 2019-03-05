#include "driver/OpenGL.h"

// Include GLEW. Always include it before gl.h and glfw.h, since it's a bit magic.
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace GameEngine
{
	Driver_OpenGL::Driver_OpenGL()
	{

	}

	Driver_OpenGL::~Driver_OpenGL()
	{

	}

	int Driver_OpenGL::Initialize()
	{
		glEnable(GL_MULTISAMPLE);

		// Enable depth test
		glEnable(GL_DEPTH_TEST);
		// Accept fragment if it closer to the camera than the former one
		glDepthFunc(GL_LESS);

		// Cull triangles which normal is not towards the camera
		glEnable(GL_CULL_FACE);

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
		// flip screen
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