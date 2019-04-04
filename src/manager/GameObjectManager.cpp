#include "manager/GameObjectManager.h"
#include "Engine.h"

namespace GameEngine
{
	GameObject::GameObject()
	{
		m_Name = "Game Object";
	}

	GameObject::~GameObject()
	{

	}

	int GameObject::AddChild(GameObjectPtr obj)
	{
		Engine::GetInstance()->GetGameObjectMgr()->AddGameObject(obj, shared_from_this());

		return 0;
	}

	int GameObject::AddComponent(IComponentPtr component)
	{
		m_Components.push_back(std::move(component));

		return 0;
	}

	GameObjectManager::GameObjectManager()
	{

	}

	GameObjectManager::~GameObjectManager()
	{

	}

	int GameObjectManager::Initialize()
	{
		m_RootGameObj = std::make_shared<GameObject>();
		return 0;
	}

	int GameObjectManager::Destroy()
	{
		return 0;
	}

	int GameObjectManager::AddGameObject(GameObjectPtr obj)
	{
		return AddGameObject(obj, m_RootGameObj);
	}

	int GameObjectManager::AddGameObject(GameObjectPtr obj, GameObjectPtr parent)
	{
		GameObjectPtr parentObj = obj->m_Parent.lock();
		if (parentObj)
		{
			// valid parent
			//parentObj->m_Children.remove(obj); // remove child

			obj->m_Parent = parent;
			parent->m_Children.push_back(obj);

			GameObjectEventArgs args(obj);
			args.gameObj = obj;
			Engine::GetInstance()->GetEventMgr()->SendEvent("GameObject_ParentChanged", args);
		}
		else
		{
			obj->m_Parent = parent;
			parent->m_Children.push_back(obj);

			GameObjectEventArgs args(obj);
			args.gameObj = obj;
			Engine::GetInstance()->GetEventMgr()->SendEvent("GameObject_Add", args);
		}

		return 0;
	}
}