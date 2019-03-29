#include "system/RenderSystem.h"
#include "Engine.h"

#include "rendering/Mesh.h"
#include "component/MeshComponent.h"
#include "component/TransformComponent.h"

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

		// pre calc the view and proj matrix
		glm::mat4 projMat = glm::perspective(1.3333f, glm::radians(45.0f), 0.1f, 2000.0f);
		glm::mat4 viewMat = glm::lookAt(glm::vec3(0.0f, 0.0f, 100.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		// attempt to draw test mesh
		for (auto itr = m_GameObjects.begin(); itr != m_GameObjects.end(); )
		{
			GameObjectPtr obj = (*itr).lock();

			if (obj)
			{
				// calculate model matrix
				TransformComponent* trans = obj->GetComponent<TransformComponent>();

				glm::mat4 rotation = glm::mat4(trans->GetRotation());
				glm::mat4 translation = glm::translate(trans->GetPosition());
				glm::mat4 scale = glm::scale(trans->GetScale());

				glm::mat4 modelMat = translation * rotation * scale;

				obj->GetComponent<MeshComponent>()->GetMesh()->Render(modelMat, viewMat, projMat);
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