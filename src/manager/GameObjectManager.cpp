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
		m_RootGameObj->SetName("Root");

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
			for (auto itr = parentObj->m_Children.begin(); itr != parentObj->m_Children.end(); itr++)
			{
				if ((*itr).lock() == obj)
				{
					parentObj->m_Children.erase(itr);
					break;
				}
			}

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