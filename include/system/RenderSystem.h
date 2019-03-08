#pragma once
#include "manager/SystemManager.h"

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