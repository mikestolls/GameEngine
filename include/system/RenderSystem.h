#pragma once
#include "system/SystemManager.h"

namespace GameEngine
{
	class RenderSystem : public ISystem
	{
	public:
									RenderSystem();
									~RenderSystem();

		int							Update(float dt);
		int							Render();

	};
}