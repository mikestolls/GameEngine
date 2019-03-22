#pragma once
#include "defines.h"

#include "rendering/Material.h"

namespace GameEngine
{
	struct EventArgs
	{

	};

	typedef std::function<void(EventArgs)>									EventCallbackFunc;

	class EventManager
	{
	public:

																			EventManager();
																			~EventManager();

		int																	Initialize();
		int																	Destroy();
					
		int																	RegisterEventListener(std::string eventName, EventCallbackFunc function);

		int																	SendEvent(std::string eventName, EventArgs args);
		int																	SendEvent(std::string eventName) { return SendEvent(eventName, EventArgs()); }

	private:

		std::unordered_map<std::string, std::vector<EventCallbackFunc>>		m_EventListeners;
	};

	typedef std::shared_ptr<EventManager>									EventManagerPtr;
}