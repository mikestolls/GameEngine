#include "manager/SystemManager.h"

namespace GameEngine
{
	SystemManager::SystemManager()
	{

	}

	SystemManager::~SystemManager()
	{

	}

	int SystemManager::Initialize()
	{
		return 0;
	}

	int SystemManager::Destroy()
	{
		return 0;
	}

	int SystemManager::Update(float dt)
	{
		for (SystemPtr system : m_Systems)
		{
			bool ret = system->Update(dt);

			// a system wants to kill the app
			if (ret != 0)
			{
				return ret;
			}
		}

		return 0;
	}

	int SystemManager::Render()
	{
		for (SystemPtr system : m_Systems)
		{
			system->Render();
		}

		return 0;
	}

	void SystemManager::RegisterSystem(SystemPtr system)
	{
		m_Systems.push_back(system);
	}

	void SystemManager::UnregisterSystem(SystemPtr system)
	{
		//m_Systems.erase(system);
	}
}