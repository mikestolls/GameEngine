#pragma once

#include "driver/Driver_OpenGL.h"
#include "ui/ImguiDriver.h"
#include "manager/SystemManager.h"
#include "manager/MaterialManager.h"
#include "manager/ShaderManager.h"
#include "manager/TextureManager.h"
#include "manager/GameObjectManager.h"
#include "manager/EventManager.h"

#include "EventArgs.h"

namespace GameEngine
{
	class Engine
	{
	public:

		static Engine*					GetInstance();

		int								Initialize(DriverPtr driver);
		int								Destroy();

		inline DriverPtr				GetDriver() { return m_Driver; }
		inline ShaderManagerPtr			GetShaderMgr() { return m_ShaderMgr; }
		inline MaterialManagerPtr		GetMaterialMgr() { return m_MaterialMgr; }
		inline TextureManagerPtr		GetTextureMgr() { return m_TextureMgr; }
		inline GameObjectManagerPtr		GetGameObjectMgr() { return m_GameObjectMgr; }
		inline EventManagerPtr			GetEventMgr() { return m_EventMgr; }

	private:

										Engine();
										~Engine();

		int								Update(EventArgs& args);

		static Engine*					s_Instance;

		bool							m_RequestDestroy;

		DriverPtr						m_Driver;
		SystemManagerPtr				m_SystemMgr;
		ShaderManagerPtr				m_ShaderMgr;
		MaterialManagerPtr				m_MaterialMgr;
		TextureManagerPtr				m_TextureMgr;
		GameObjectManagerPtr			m_GameObjectMgr;
		EventManagerPtr					m_EventMgr;
	};
}