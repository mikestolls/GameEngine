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
		m_EventMgr = std::make_shared<EventManager>();
	}

	Engine::~Engine()
	{
		// initialize manager
		m_SystemMgr->Destroy();
		m_ShaderMgr->Destroy();
		m_MaterialMgr->Destroy();
		m_TextureMgr->Destroy();
		m_GameObjectMgr->Destroy();
		m_EventMgr->Destroy();

		m_SystemMgr = nullptr;
		m_ShaderMgr = nullptr;
		m_MaterialMgr = nullptr;
		m_TextureMgr = nullptr;
		m_GameObjectMgr = nullptr;
		m_EventMgr = nullptr;
	}

	int Engine::Initialize(DriverPtr driver, UI::ImguiDriverPtr imguiDriver)
	{
		m_Driver = driver;
		m_ImguiDriver = imguiDriver;

		// initialize manager
		m_SystemMgr->Initialize();
		m_ShaderMgr->Initialize();
		m_MaterialMgr->Initialize();
		m_TextureMgr->Initialize();
		m_GameObjectMgr->Initialize();
		m_EventMgr->Initialize();

		m_EventMgr->RegisterEventListener("Frame_Update", std::bind(&Engine::Update, this, std::placeholders::_1));

		return 0;
	}

	int Engine::Destroy()
	{
		return 0;
	}

	int Engine::Update(EventArgs& args)
	{
		// engine update
		m_EventMgr->SendEvent("System_Update");

		return 0;
	}
}