#pragma once
#include "manager/SystemManager.h"
#include "EventArgs.h"
#include "rendering/Mesh.h"

namespace GameEngine
{
	class RenderSystem : public ISystem
	{
	public:
									RenderSystem();
									~RenderSystem();
																	   
		int							Initialize();
		int							Destroy();

	private:

		void						Update(EventArgs& args);

		void						GameObjectAdd(EventArgs& args);
		void						GameObjectRemove(EventArgs& args);
		
		std::vector<GameObjectPtr>	m_GameObjects;
	};
}