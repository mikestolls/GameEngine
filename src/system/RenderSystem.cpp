#include "system/RenderSystem.h"
#include "Engine.h"

#include "rendering/Mesh.h"
#include "component/MeshComponent.h"
#include "component/CameraComponent.h"
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

		// grab the first camera you have
		if (m_CameraGameObjects.size() == 0)
		{
			return;
		}

		GameObjectPtr camObj = (*m_CameraGameObjects.begin()).lock();
		CameraComponent* cam = camObj->GetComponent<CameraComponent>();
		TransformComponent* camTrans = camObj->GetComponent<TransformComponent>();

		if (!cam || !camTrans)
		{
			return;
		}

		// pre calc the view and proj matrix
		glm::mat4 projMat = glm::perspective(cam->GetAspect(), cam->GetFov(), cam->GetNearClip(), cam->GetFarClip());

		// Calculate the new Front vector
		glm::quat rotMat = glm::mat4(glm::quat(camTrans->GetRotation()));
		glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
		front = glm::normalize(rotMat * front);

		// Also re-calculate the Right and Up vector
		glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
		right = glm::normalize(rotMat * right);

		glm::vec3 up = glm::normalize(glm::cross(right, front));

		glm::mat4 viewMat = glm::lookAt(camTrans->GetPosition(), camTrans->GetPosition() + front, up);

		// attempt to draw test mesh
		for (auto itr = m_MeshGameObjects.begin(); itr != m_MeshGameObjects.end(); )
		{
			GameObjectPtr obj = (*itr).lock();

			if (obj)
			{
				// calculate model matrix
				TransformComponent* trans = obj->GetComponent<TransformComponent>();

				glm::mat4 rotation = glm::mat4(glm::quat(trans->GetRotation()));
				glm::mat4 translation = glm::translate(trans->GetPosition());
				glm::mat4 scale = glm::scale(trans->GetScale());

				glm::mat4 modelMat = translation * rotation * scale;

				obj->GetComponent<MeshComponent>()->GetMesh()->Render(modelMat, viewMat, projMat);
			}
			else
			{
				// expired
				itr = m_MeshGameObjects.erase(itr);
				continue;
			}

			itr++; // we move iterator here to account for erase
		}
	}

	void RenderSystem::AddGameObject(GameObjectWeakPtr gameObj)
	{
		GameObjectPtr obj = gameObj.lock();

		if (obj)
		{
			// calculate model matrix
			MeshComponent* mesh = obj->GetComponent<MeshComponent>();
			CameraComponent* cam = obj->GetComponent<CameraComponent>();

			if (mesh)
			{
				m_MeshGameObjects.push_front(gameObj);
			}

			if (cam)
			{
				m_CameraGameObjects.push_front(gameObj);
			}
		}
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
			for (auto itr = m_MeshGameObjects.begin(); itr != m_MeshGameObjects.end(); itr++)
			{
				if ((*itr).lock() == obj)
				{
					itr = m_MeshGameObjects.erase(itr);
					return;
				}
			}
		}
	}
}