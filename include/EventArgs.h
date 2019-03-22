#pragma once

#include "manager/EventManager.h"

namespace GameEngine
{
	struct FrameEventArgs : public EventArgs
	{
		float deltaTime;
	};
}