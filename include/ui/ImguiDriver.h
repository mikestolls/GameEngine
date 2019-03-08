#pragma once
#include "defines.h"
#include "driver/Driver_OpenGL.h"

namespace GameEngine
{
	namespace UI
	{
		class ImguiDriver
		{
		public:

												ImguiDriver();
												~ImguiDriver();

			int									Initialize(void* handle, DriverPtr driver);
			int									Destroy();

		private:

			DriverPtr							m_Driver;
		};

		typedef std::shared_ptr<ImguiDriver>	ImguiDriverPtr;
	}
}