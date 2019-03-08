#pragma once
#include "platform/Platform_Windows.h"
#include "driver/Driver_OpenGL.h"

namespace GameEngine
{
	class SystemManager;

	class Engine
	{
	public:

		static Engine*				GetInstance();

		int							Initialize(DriverPtr driver);
		int							Destroy();

		int							Update(float dt);

		inline DriverPtr			GetDriver() { return m_Driver; }

	private:

									Engine();
									~Engine();

		static Engine*				s_Instance;

		DriverPtr					m_Driver;
		SystemManager*				m_SystemMgr;
	};
}