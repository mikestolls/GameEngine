#pragma once
#include "manager/SystemManager.h"

namespace GameEngine
{
	class IComponent
	{
	public:
													IComponent() { }
		virtual										~IComponent() { }

		inline std::string							GetName() { return m_Name; }

	protected:

		std::string									m_Name;
	};

	typedef std::shared_ptr<IComponent>				IComponentPtr;

	class GameObject;
	typedef std::shared_ptr<GameObject>				GameObjectPtr;

	class GameObject
	{
	public:
													GameObject();
													~GameObject();

		int											AddChild(GameObjectPtr obj);
		int											AddComponent(IComponentPtr component);

	private:

		std::vector<GameObjectPtr>					m_Children;
		std::vector<IComponentPtr>					m_Components;
	};

	class GameObjectSystem : public ISystem
	{
	public:
													GameObjectSystem();
													~GameObjectSystem();

		int											Update(float dt);
		int											Render();

		int											AddGameObject(GameObjectPtr obj);
		int											AddGameObject(GameObjectPtr obj, GameObjectPtr parent);

	private:

		GameObjectPtr								m_RootGameObj;
	};
}