#pragma once

#include "manager/EventManager.h"
#include "manager/GameObjectManager.h"

namespace GameEngine
{
	struct FrameEventArgs : EventArgs
	{
		FrameEventArgs(float dt) : EventArgs() { deltaTime = dt; }

		float deltaTime;
	};

	struct GameObjectEventArgs : EventArgs
	{
		GameObjectEventArgs(GameObjectPtr obj) : EventArgs() { gameObj = obj; }

		GameObjectPtr gameObj;
	};
}