#include "component/TransformComponent.h"

namespace GameEngine
{
	TransformComponent::TransformComponent() : IComponent()
	{
		m_Name = "Transform Component";

		m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
		m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	}

	TransformComponent::~TransformComponent()
	{

	}
}