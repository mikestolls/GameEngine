#pragma once
#include "manager/SystemManager.h"
#include "manager/EventManager.h"
#include "manager/GameObjectManager.h"
#include "rendering/FrameBuffer_OpenGL.h"

namespace GameEngine
{
	class EditorSystem : public ISystem
	{
	public:
									EditorSystem();
									~EditorSystem();

		int							Initialize();
		int							Destroy();

	private:

		void						Update();
		void						PreUpdate();
		void						PostUpdate();

		void						UpdateMainMenuBar();
		void						UpdateHierarchyPanel();
		void						UpdateInspectorPanel();
		void						UpdateScenePanel();

		void						UpdateHierarchyTreeRecursive(GameObjectWeakPtr obj);

		void						GameObjectAddCallback(EventArgs& args);

		//GameObjectWeakPtr			m_Camera;

		FrameBufferPtr				m_SceneFrameBuffer;
	};
}