#include "Engine.h"
#include "system/RenderSystem.h"
#include "system/EditorSystem.h"

namespace GameEngine
{
	Engine* Engine::s_Instance = nullptr;

	Engine* Engine::GetInstance()
	{
		if (s_Instance == nullptr)
		{
			s_Instance = new Engine();
		}

		return s_Instance;
	}

	Engine::Engine()
	{
		m_SystemMgr = std::make_shared<SystemManager>();
		m_ShaderMgr = std::make_shared<ShaderManager>();
		m_MaterialMgr = std::make_shared<MaterialManager>();
		m_TextureMgr = std::make_shared<TextureManager>();
		m_GameObjectMgr = std::make_shared<GameObjectManager>();
	}

	Engine::~Engine()
	{
		// initialize manager
		m_SystemMgr->Destroy();
		m_ShaderMgr->Destroy();
		m_MaterialMgr->Destroy();
		m_TextureMgr->Destroy();
		m_GameObjectMgr->Destroy();

		m_SystemMgr = nullptr;
		m_ShaderMgr = nullptr;
		m_MaterialMgr = nullptr;
	}

	int Engine::Initialize(DriverPtr driver)
	{
		m_Driver = driver;

		// initialize manager
		m_SystemMgr->Initialize();
		m_ShaderMgr->Initialize();
		m_MaterialMgr->Initialize();
		m_TextureMgr->Initialize();
		m_GameObjectMgr->Initialize();

		// add systems. eventually replace this with a bootstrap that handles system dependency and order
		m_SystemMgr->RegisterSystem(std::make_shared<RenderSystem>());
		m_SystemMgr->RegisterSystem(std::make_shared<EditorSystem>());

		return 0;
	}

	int Engine::Destroy()
	{
		return 0;
	}

	int Engine::Update(float dt)
	{
		// engine update
		int ret = m_SystemMgr->Update(dt);

		// engine render
		m_SystemMgr->Render();

		return ret;
	}
}