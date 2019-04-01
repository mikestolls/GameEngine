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
																	   
		int									Initialize();
		int									Destroy();

	private:

		void								Update(EventArgs& args);

		void								AddGameObject(GameObjectWeakPtr gameObj);

		void								GameObjectAddCallback(EventArgs& args);
		void								GameObjectRemoveCallback(EventArgs& args);
		
		std::list<GameObjectWeakPtr>		m_MeshGameObjects;
		std::list<GameObjectWeakPtr>		m_CameraGameObjects;
	};
}