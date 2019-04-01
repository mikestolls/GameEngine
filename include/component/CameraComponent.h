#pragma once
#include "manager/GameObjectManager.h"

namespace GameEngine
{
	class CameraComponent : public IComponent
	{
	public:

		enum
		{
			PROJECTION_TYPE_ORTHOGONAL = 0,
			PROJECTION_TYPE_PERSPECTIVE,
		};

											CameraComponent();
											~CameraComponent();

		void								SetFov(float fov) { m_Fov = fov; }
		float								GetFov() { return m_Fov; }

		void								SetAspect(float aspect) { m_Aspect = aspect; }
		float								GetAspect() { return m_Aspect; }

		void								SetNearClip(float nearClip) { m_NearClip = nearClip; }
		float								GetNearClip() { return m_NearClip; }

		void								SetFarClip(float farClip) { m_FarClip = farClip; }
		float								GetFarClip() { return m_FarClip; }

		void								SetPRojectionType(int type) { m_ProjectionType = type; }
		int									GetProjectionType() { return m_ProjectionType; }

	private:

		float								m_Fov;
		float								m_Aspect;
		float								m_NearClip;
		float								m_FarClip;
		int									m_ProjectionType;
	};
}