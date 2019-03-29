#pragma once
#include "manager/GameObjectManager.h"

namespace GameEngine
{
	class TransformComponent : public IComponent
	{
	public:
											TransformComponent();
											~TransformComponent();

		inline void							SetPosition(glm::vec3 position) { m_Position = position; }
		inline void							SetPosition(float x, float y, float z) { m_Position = glm::vec3(x, y, z); }
		inline glm::vec3					GetPosition() { return m_Position; }

		inline void							SetRotation(glm::vec3 rotation) { m_Rotation = glm::quat(rotation); }
		inline void							SetRotation(float x, float y, float z) { m_Rotation = glm::quat(glm::vec3(glm::radians(x), glm::radians(y), glm::radians(z))); }
		inline glm::quat					GetRotation() { return m_Rotation; }

		inline void							SetScale(glm::vec3 scale) { m_Scale = scale; }
		inline void							SetScale(float x, float y, float z) { m_Scale = glm::vec3(x, y, z); }
		inline glm::vec3					GetScale() { return m_Scale; }

	private:

		glm::vec3							m_Position;
		glm::quat							m_Rotation;
		glm::vec3							m_Scale;
	};
}