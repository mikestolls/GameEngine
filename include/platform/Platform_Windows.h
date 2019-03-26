#pragma once
#include "defines.h"

#include "Engine.h"
#include "driver/Driver_OpenGL.h"
#include "ui/ImguiDriver.h"

namespace GameEngine
{
	// putting interface here for now
	class IPlatform
	{
	public:
										IPlatform() { }
										~IPlatform() { }

		virtual int						Initialize() = 0;
		virtual int						Destroy() = 0;

		virtual int						Run() = 0;

	protected:

		int								m_ScreenWidth;
		int								m_ScreenHeight;
	};

	typedef std::shared_ptr<IPlatform>	PlatformPtr;

	class Platform_Windows : public IPlatform
	{
	private:

	public:
										Platform_Windows(const char* windowName, int screenWidth, int screenHeight);
										~Platform_Windows();

		int								Initialize();
		int								Destroy();
		
		int								Run();

		void							Shutdown();

	private:

		int								UpdateMouse();

		bool							m_IsRunning;

		std::string						m_WindowName;

		DriverPtr						m_Driver;
		UI::ImguiDriverPtr				m_ImguiDriver;
	};
}