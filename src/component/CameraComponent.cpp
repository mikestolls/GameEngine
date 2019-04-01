#include "component/CameraComponent.h"

namespace GameEngine
{
	CameraComponent::CameraComponent() : IComponent()
	{
		m_Name = "Camera Component";

		m_Fov = glm::radians(60.0f);
		m_Aspect = 1.7777f;
		m_NearClip = 0.1f;
		m_FarClip = 20000.0f;
		m_ProjectionType = PROJECTION_TYPE_PERSPECTIVE;
	}

	CameraComponent::~CameraComponent()
	{

	}
}