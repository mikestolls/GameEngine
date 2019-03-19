#pragma once
#include "platform/Platform_Windows.h"
#include "driver/Driver_OpenGL.h"
#include "manager/SystemManager.h"
#include "manager/MaterialManager.h"
#include "manager/ShaderManager.h"
#include "manager/TextureManager.h"

namespace GameEngine
{
	class Engine
	{
	public:

		static Engine*				GetInstance();

		int							Initialize(DriverPtr driver);
		int							Destroy();

		int							Update(float dt);

		inline DriverPtr			GetDriver() { return m_Driver; }
		inline ShaderManagerPtr		GetShaderMgr() { return m_ShaderMgr; }
		inline MaterialManagerPtr	GetMaterialMgr() { return m_MaterialMgr; }
		inline TextureManagerPtr	GetTextureMgr() { return m_TextureMgr; }

	private:

									Engine();
									~Engine();

		static Engine*				s_Instance;

		DriverPtr					m_Driver;
		SystemManagerPtr			m_SystemMgr;
		ShaderManagerPtr			m_ShaderMgr;
		MaterialManagerPtr			m_MaterialMgr;
		TextureManagerPtr			m_TextureMgr;
	};
}