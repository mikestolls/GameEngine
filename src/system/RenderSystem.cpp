#include "system/RenderSystem.h"
#include "Engine.h"

#include "rendering/Mesh.h"
#include "component/MeshComponent.h"

namespace GameEngine
{
	RenderSystem::RenderSystem()
	{

	}

	RenderSystem::~RenderSystem()
	{

	}

	int RenderSystem::Initialize()
	{
		Engine* engine = Engine::GetInstance();

		engine->GetDriver()->SetClearColor(0.5f, 0.5f, 0.5f, 1.0f);

		engine->GetEventMgr()->RegisterEventListener("System_Update", std::bind(&RenderSystem::Update, this, std::placeholders::_1));
		engine->GetEventMgr()->RegisterEventListener("GameObject_Add", std::bind(&RenderSystem::GameObjectAdd, this, std::placeholders::_1));
		engine->GetEventMgr()->RegisterEventListener("GameObject_Remove", std::bind(&RenderSystem::GameObjectRemove, this, std::placeholders::_1));

		return 0;
	}

	int RenderSystem::Destroy()
	{
		return 0;
	}

	void RenderSystem::Update(EventArgs& args)
	{
		Engine::GetInstance()->GetDriver()->Clear(IDriver::CLEAR_COLOR);

		// attempt to draw test mesh
		for (auto itr = m_GameObjects.begin(); itr != m_GameObjects.end(); itr++)
		{
			(*itr)->GetComponent<MeshComponent>()->GetMesh()->Render();
		}
	}

	void RenderSystem::GameObjectAdd(EventArgs& args)
	{
		GameObjectEventArgs* gameObjArgs = static_cast<GameObjectEventArgs*>(&args);

		m_GameObjects.push_back(gameObjArgs->gameObj);
	}

	void RenderSystem::GameObjectRemove(EventArgs& args)
	{
		GameObjectEventArgs* gameObjArgs = static_cast<GameObjectEventArgs*>(&args);
	}
}