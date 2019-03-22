#pragma once
#include "defines.h"

#include "rendering/Material.h"

namespace GameEngine
{
	typedef std::function<void()>											EventCallbackFunc;

	class EventManager
	{
	public:

																			EventManager();
																			~EventManager();

		int																	Initialize();
		int																	Destroy();
					
		int																	RegisterEventListener(std::string eventName, EventCallbackFunc function);
		
		int																	SendEvent(std::string eventName);

	private:

		std::unordered_map<std::string, std::vector<EventCallbackFunc>>		m_EventListeners;
	};

	typedef std::shared_ptr<EventManager>									EventManagerPtr;
}