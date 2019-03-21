#include "system/GameObjectSystem.h"
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
		m_Components.push_back(component);

		return 0;
	}

	GameObjectSystem::GameObjectSystem()
	{

	}

	GameObjectSystem::~GameObjectSystem()
	{

	}

	int GameObjectSystem::Update(float dt)
	{
		return 0;
	}

	int GameObjectSystem::Render()
	{
		return 0;
	}

	int GameObjectSystem::AddGameObject(GameObjectPtr obj)
	{
		return AddGameObject(obj, m_RootGameObj);
	}

	int GameObjectSystem::AddGameObject(GameObjectPtr obj, GameObjectPtr parent)
	{
		parent->AddChild(obj);

		return 0;
	}
}