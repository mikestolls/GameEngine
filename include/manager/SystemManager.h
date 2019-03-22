#pragma once
#include "defines.h"

namespace GameEngine
{
	class ISystem
	{
	public:
											ISystem() { }
		virtual 							~ISystem() { }


		virtual int							Initialize() = 0;
		virtual int							Destroy() = 0;
	};

	typedef std::shared_ptr<ISystem>		ISystemPtr;

	class SystemManager
	{
	public:
											SystemManager();
											~SystemManager();


		int									Initialize();
		int									Destroy();

	private:

		std::vector< ISystemPtr>			m_Systems;
	};

	typedef std::shared_ptr<SystemManager>	SystemManagerPtr;
}
