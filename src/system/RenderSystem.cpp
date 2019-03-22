#include "system/RenderSystem.h"
#include "Engine.h"

#include "rendering/Mesh.h"

namespace GameEngine
{
	RenderSystem::RenderSystem()
	{
		Engine::GetInstance()->GetDriver()->SetClearColor(0.5f, 0.5f, 0.5f, 1.0f);

		MeshPtr mesh = std::make_shared<Mesh>("mesh/minifig.fbx");
	}

	RenderSystem::~RenderSystem()
	{

	}

	int RenderSystem::Update(float dt)
	{
		Engine::GetInstance()->GetDriver()->Clear(IDriver::CLEAR_COLOR);

		return 0;
	}

	int RenderSystem::Render()
	{
		return 0;
	}
}