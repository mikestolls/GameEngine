#include "manager/SystemManager.h"

namespace GameEngine
{
	SystemManager::SystemManager()
	{

	}

	SystemManager::~SystemManager()
	{

	}

	int SystemManager::Update(float dt)
	{
		for (SystemPtr system : m_Systems)
		{
			system->Update(dt);
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