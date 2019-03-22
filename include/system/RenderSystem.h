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

		void						Update(EventArgs args);

	private:
		
		std::vector<MeshPtr>		m_Meshes;
	};
}