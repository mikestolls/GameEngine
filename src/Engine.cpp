#include "Engine.h"
#include "system/RenderSystem.h"

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
	}

	Engine::~Engine()
	{
		m_SystemMgr = nullptr;
		m_ShaderMgr = nullptr;
		m_MaterialMgr = nullptr;
	}

	int Engine::Initialize(DriverPtr driver)
	{
		m_Driver = driver;

		// add systems
		m_SystemMgr->RegisterSystem(std::make_shared<RenderSystem>());

		return 0;
	}

	int Engine::Destroy()
	{
		return 0;
	}

	int Engine::Update(float dt)
	{
		// engine update
		m_SystemMgr->Update(dt);

		// engine render
		m_SystemMgr->Render();

		return 0;
	}
}