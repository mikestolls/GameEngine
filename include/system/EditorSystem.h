#pragma once
#include "manager/SystemManager.h"

namespace GameEngine
{
	class EditorSystem : public ISystem
	{
	public:
									EditorSystem();
									~EditorSystem();

		int							Initialize();
		int							Destroy();

		void						Update();

	};
}