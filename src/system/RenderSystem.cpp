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
		engine->GetEventMgr()->RegisterEventListener("GameObject_Add", std::bind(&RenderSystem::GameObjectAddCallback, this, std::placeholders::_1));
		engine->GetEventMgr()->RegisterEventListener("GameObject_Remove", std::bind(&RenderSystem::GameObjectRemoveCallback, this, std::placeholders::_1));

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
		for (auto itr = m_GameObjects.begin(); itr != m_GameObjects.end(); )
		{
			GameObjectPtr obj = (*itr).lock();

			if (obj)
			{
				obj->GetComponent<MeshComponent>()->GetMesh()->Render();
			}
			else
			{
				// expired
				itr = m_GameObjects.erase(itr);
				continue;
			}

			itr++; // we move iterator here to account for erase
		}
	}

	void RenderSystem::AddGameObject(GameObjectWeakPtr gameObj)
	{
		m_GameObjects.push_front(gameObj);
	}

	void RenderSystem::GameObjectAddCallback(EventArgs& args)
	{
		GameObjectEventArgs* gameObjArgs = static_cast<GameObjectEventArgs*>(&args);
		GameObjectPtr obj = gameObjArgs->gameObj.lock();

		if (obj) // check it hasnt expired
		{
			AddGameObject(obj);
		}
	}

	void RenderSystem::GameObjectRemoveCallback(EventArgs& args)
	{
		GameObjectEventArgs* gameObjArgs = static_cast<GameObjectEventArgs*>(&args);
		GameObjectPtr obj = gameObjArgs->gameObj.lock();

		if (obj) // check it hasnt expired. if it has it will be removed during update
		{
			for (auto itr = m_GameObjects.begin(); itr != m_GameObjects.end(); itr++)
			{
				if ((*itr).lock() == obj)
				{
					itr = m_GameObjects.erase(itr);
					return;
				}
			}
		}
	}
}