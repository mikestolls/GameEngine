#pragma once
#include "defines.h"

namespace GameEngine
{
	class ISystem
	{
	public:
											ISystem() { }
		virtual 							~ISystem() { }

		virtual int							Update(float dt) = 0;
		virtual int							Render() = 0;
	};

	typedef std::shared_ptr<ISystem>		SystemPtr;

	class SystemManager
	{
	public:
											SystemManager();
											~SystemManager();

		int									Update(float dt);
		int									Render();

		void								RegisterSystem(SystemPtr system);
		void								UnregisterSystem(SystemPtr system);

	private:

		std::vector<SystemPtr>				m_Systems;
	};

	typedef std::shared_ptr<SystemManager>	SystemManagerPtr;
}
