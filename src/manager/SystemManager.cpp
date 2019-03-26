#include "manager/SystemManager.h"
#include "system/RenderSystem.h"
#include "system/EditorSystem.h"

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
		// create and initialize the systems
		m_Systems.push_back(std::make_shared<RenderSystem>());
		m_Systems.push_back(std::make_shared<EditorSystem>());

		for (auto itr = m_Systems.begin(); itr != m_Systems.end(); itr++)
		{
			(*itr)->Initialize();
		}

		return 0;
	}

	int SystemManager::Destroy()
	{
		for (auto itr = m_Systems.begin(); itr != m_Systems.end(); itr++)
		{
			(*itr)->Initialize();
		}

		m_Systems.clear();

		return 0;
	}
}