#include "manager/GameObjectManager.h"
#include "Engine.h"

namespace GameEngine
{
	GameObject::GameObject()
	{

	}

	GameObject::~GameObject()
	{

	}

	int GameObject::AddChild(GameObjectPtr obj)
	{
		m_Children.push_back(obj);

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
		parent->AddChild(obj);
	
		GameObjectEventArgs args(obj);
		args.gameObj = obj;
		Engine::GetInstance()->GetEventMgr()->SendEvent("GameObject_Add", args);

		return 0;
	}
}