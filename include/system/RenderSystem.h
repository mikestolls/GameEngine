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
		virtual 							~RenderSystem();
																	   
		virtual int							Initialize();
		virtual int							Destroy();

	protected:

		virtual void						Update(EventArgs& args);

		void								AddGameObject(GameObjectWeakPtr gameObj);

		void								GameObjectAddCallback(EventArgs& args);
		void								GameObjectRemoveCallback(EventArgs& args);
		
		std::list<GameObjectWeakPtr>		m_MeshGameObjects;
		std::list<GameObjectWeakPtr>		m_CameraGameObjects;
	};
}