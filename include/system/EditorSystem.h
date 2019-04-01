#pragma once
#include "manager/SystemManager.h"
#include "manager/EventManager.h"
#include "manager/GameObjectManager.h"

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

		void						GameObjectAddCallback(EventArgs& args);

		GameObjectPtr				m_Camera;
	};
}