#pragma once
#include "defines.h"

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

	typedef std::unique_ptr<IComponent>				IComponentPtr;
	typedef std::weak_ptr<IComponent>				IComponentWeakPtr;

	class GameObject;
	typedef std::shared_ptr<GameObject>				GameObjectPtr;
	typedef std::weak_ptr<GameObject>				GameObjectWeakPtr;

	class GameObject
	{
	public:
													GameObject();
													~GameObject();

		int											AddChild(GameObjectPtr obj);
		int											AddComponent(IComponentPtr component);

		template <typename T>
		T*											GetComponent()
		{
			for (auto itr = m_Components.begin(); itr != m_Components.end(); itr++)
			{
				// if true than the class matches. Note: im sure there is a way to improve this
				T* comp = dynamic_cast<T*>((*itr).get());
				if (comp)
				{
					return comp;
				}
			}

			return nullptr;
		}

	private:

		std::vector<GameObjectPtr>					m_Children;
		std::vector<IComponentPtr>					m_Components;
	};

	class GameObjectManager
	{
	public:
													GameObjectManager();
													~GameObjectManager();

		int											Initialize();
		int											Destroy();

		inline GameObjectPtr						GetRootGameObj() { return m_RootGameObj; }

		int											AddGameObject(GameObjectPtr obj);
		int											AddGameObject(GameObjectPtr obj, GameObjectPtr parent);

	private:

		GameObjectPtr								m_RootGameObj;
	};

	typedef std::shared_ptr<GameObjectManager>		GameObjectManagerPtr;
}