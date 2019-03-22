#include "system/RenderSystem.h"
#include "Engine.h"

#include "rendering/Mesh.h"

namespace GameEngine
{
	RenderSystem::RenderSystem()
	{
		Engine::GetInstance()->GetDriver()->SetClearColor(0.5f, 0.5f, 0.5f, 1.0f);

		MeshPtr mesh = std::make_shared<Mesh>("mesh/minifig.fbx");
		m_Meshes.push_back(mesh);
	}

	RenderSystem::~RenderSystem()
	{

	}

	int RenderSystem::Initialize()
	{
		Engine::GetInstance()->GetEventMgr()->RegisterEventListener("System_Update", std::bind(&RenderSystem::Update, this, std::placeholders::_1));

		return 0;
	}

	int RenderSystem::Destroy()
	{
		return 0;
	}

	void RenderSystem::Update(EventArgs args)
	{
		Engine::GetInstance()->GetDriver()->Clear(IDriver::CLEAR_COLOR);

		// attempt to draw test mesh
		for (auto itr = m_Meshes.begin(); itr != m_Meshes.end(); itr++)
		{
			(*itr)->Render();
		}
	}
}