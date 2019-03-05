#include "system/RenderSystem.h"
#include "Engine.h"

namespace GameEngine
{
	RenderSystem::RenderSystem()
	{
		Engine::GetInstance()->GetDriver()->SetClearColor(1.0f, 0.0f, 0.0f, 1.0f);
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