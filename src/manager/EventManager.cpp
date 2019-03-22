#include "manager/EventManager.h"
#include "Engine.h"

namespace GameEngine
{
	EventManager::EventManager()
	{

	}

	EventManager::~EventManager()
	{

	}

	int EventManager::Initialize()
	{
		return 0;
	}

	int EventManager::Destroy()
	{
		return 0;
	}

	int EventManager::RegisterEventListener(std::string eventName, EventCallbackFunc function)
	{
		m_EventListeners[eventName].push_back(function);

		return 0;
	}

	int EventManager::SendEvent(std::string eventName)
	{
		int count = 0;

		auto itr = m_EventListeners.find(eventName);

		if (itr == m_EventListeners.end())
		{
			return count;
		}

		// loop over listener callbacks and dispatch
		for (auto vitr = itr->second.begin(); vitr != itr->second.end(); vitr++)
		{
			(*vitr)();
			count++;
		}

		return count;
	}
}