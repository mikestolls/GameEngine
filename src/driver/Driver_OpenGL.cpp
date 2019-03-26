#include "driver/Driver_OpenGL.h"

#include <GL/gl3w.h>

#include <Engine.h>
#include <manager/EventManager.h>

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
		// setup frame event callback
		Engine::GetInstance()->GetEventMgr()->RegisterEventListener("Frame_PreUpdate", std::bind(&Driver_OpenGL::PreUpdate, this));
		Engine::GetInstance()->GetEventMgr()->RegisterEventListener("Frame_PostUpdate", std::bind(&Driver_OpenGL::PostUpdate, this));

		return 0;
	}

	int Driver_OpenGL::Destroy()
	{
		return 0;
	}

	void Driver_OpenGL::PreUpdate()
	{
		glViewport(m_ViewportRect.a.x, m_ViewportRect.a.y, m_ViewportRect.b.x, m_ViewportRect.b.y);
		Clear(CLEAR_COLOR | CLEAR_DEPTH | CLEAR_STENCIL);
	}

	void Driver_OpenGL::PostUpdate()
	{

	}

	void Driver_OpenGL::SetClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void Driver_OpenGL::Clear(int clear)
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