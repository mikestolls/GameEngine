#pragma once
#include "manager/SystemManager.h"
#include "manager/EventManager.h"
#include "manager/GameObjectManager.h"
#include "system/RenderSystem.h"
#include "rendering/FrameBuffer_OpenGL.h"

namespace GameEngine
{
	class EditorSystem : public RenderSystem
	{
	public:
									EditorSystem();
									~EditorSystem();

		int							Initialize();
		int							Destroy();

	private:

		void						Update(EventArgs& args);

		void						UpdateMainMenuBar();
		void						UpdateHierarchyPanel();
		void						UpdateInspectorPanel();
		void						UpdateScenePanel();

		void						UpdateHierarchyTreeRecursive(GameObjectWeakPtr obj);

		FrameBufferPtr				m_SceneFrameBuffer;
	};
}