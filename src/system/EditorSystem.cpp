#include "system/EditorSystem.h"
#include "Engine.h"
#include "component/CameraComponent.h"
#include "component/TransformComponent.h"

#include "imgui.h"

namespace GameEngine
{
	float camera_rot[] = { 0.0f, 0.0f, 0.0f };
	float camera_fov = 100.0f;
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	EditorSystem::EditorSystem()
	{

	}

	EditorSystem::~EditorSystem()
	{

	}

	int EditorSystem::Initialize()
	{
		Engine::GetInstance()->GetEventMgr()->RegisterEventListener("System_Update", std::bind(&EditorSystem::Update, this));
		Engine::GetInstance()->GetEventMgr()->RegisterEventListener("Frame_PreUpdate", std::bind(&EditorSystem::PreUpdate, this));
		Engine::GetInstance()->GetEventMgr()->RegisterEventListener("Frame_PostUpdate", std::bind(&EditorSystem::PostUpdate, this));

		Engine::GetInstance()->GetEventMgr()->RegisterEventListener("GameObject_Add", std::bind(&EditorSystem::GameObjectAddCallback, this, std::placeholders::_1));

		m_SceneFrameBuffer = std::make_shared<FrameBuffer_OpenGL>(1024, 1024, IFrameBuffer::FRAMEBUFFER_COLORTEXTURE0 | IFrameBuffer::FRAMEBUFFER_DEPTHBUFFER);

		return 0;
	}

	int EditorSystem::Destroy()
	{
		m_SceneFrameBuffer = nullptr;

		return 0;
	}

	void EditorSystem::Update()
	{
		// pop frame buffer
		m_SceneFrameBuffer->Pop();

		// start test
		/*ImGui::Begin("Hello, world!");

		ImGui::SetWindowSize(ImVec2(300, 150));

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("fov", &camera_fov, 1.0f, 360.0f);
		ImGui::SliderFloat3("camera rot", camera_rot, 0.0f, 360.f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		ImGui::End();

		Engine::GetInstance()->GetDriver()->SetClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);

		if (m_Camera)
		{
			m_Camera->GetComponent<TransformComponent>()->SetRotation(camera_rot[0], camera_rot[1], camera_rot[2]);
			m_Camera->GetComponent<CameraComponent>()->SetFov(camera_fov);
		}*/
		// end test

		ImGuiWindowFlags windowFlags = 0;
		windowFlags |= ImGuiWindowFlags_NoTitleBar;
		windowFlags |= ImGuiWindowFlags_NoScrollbar;
		windowFlags |= ImGuiWindowFlags_MenuBar;
		windowFlags |= ImGuiWindowFlags_NoMove;
		windowFlags |= ImGuiWindowFlags_NoResize;
		windowFlags |= ImGuiWindowFlags_NoCollapse;
		windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

		ImVec2 main_viewport_pos = ImGui::GetMainViewport()->Pos;
		ImVec2 main_viewport_size = ImGui::GetMainViewport()->Size;
		//ImGui::SetNextWindowPos(ImVec2(main_viewport_pos.x, main_viewport_pos.y));
		//ImGui::SetNextWindowSize(ImVec2(main_viewport_size.x, main_viewport_size.y));

		if (ImGui::Begin("Main", 0, windowFlags))
		{
			// docking configs
			static ImGuiDockNodeFlags dockspaceFlags = 0;

			ImGuiID dockspaceId = ImGui::GetID("DockSpace");
			ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), dockspaceFlags);

			// setup the main imgui window
			UpdateMainMenuBar();

			// update each menu
			UpdateHierarchyPanel();
			UpdateInspectorPanel();
			UpdateScenePanel();

			ImGui::End();
		}
	}
	void EditorSystem::PreUpdate()
	{
		m_SceneFrameBuffer->Push();
	}

	void EditorSystem::PostUpdate()
	{

	}

	void EditorSystem::UpdateMainMenuBar()
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				ImGui::MenuItem("New Scene");
				ImGui::MenuItem("Open Scene");
				ImGui::Separator();
				if (ImGui::MenuItem("Exit"))
				{
					Engine::GetInstance()->GetEventMgr()->SendEvent("Platform_Shutdown");
				}

				ImGui::EndMenu();
			}

			ImGui::Separator();

			if (ImGui::BeginMenu("Game Object"))
			{
				ImGui::MenuItem("New Game Object");

				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
	}

	void EditorSystem::UpdateHierarchyPanel()
	{
		// panel for heirarchy view

		ImGuiWindowFlags window_flags = 0;

		if (ImGui::Begin("Hierarchy", 0, window_flags))
		{
			for (GameObjectWeakPtr child : Engine::GetInstance()->GetGameObjectMgr()->GetRootGameObj()->GetChildren())
			{
				UpdateHierarchyTreeRecursive(child);
			}

			ImGui::End();
		}
	}

	void EditorSystem::UpdateInspectorPanel()
	{
		// panel for heirarchy view

		ImGuiWindowFlags window_flags = 0;

		if (ImGui::Begin("Inspector", 0, window_flags))
		{
			ImGui::End();
		}
	}


	void EditorSystem::UpdateScenePanel()
	{
		// panel for scene view

		ImGuiWindowFlags window_flags = 0;
		window_flags |= ImGuiWindowFlags_NoScrollbar;

		if (ImGui::Begin("Scene", 0, window_flags))
		{
			ImGuiIO& io = ImGui::GetIO();

			unsigned int texId = dynamic_cast<FrameBuffer_OpenGL*>(m_SceneFrameBuffer.get())->GetColorTextureId(0);
			ImVec2 size = ImGui::GetContentRegionMax();
			size.x -= (ImGui::GetStyle().FramePadding.x * 2.0f + ImGui::GetStyle().FrameBorderSize * 2);
			size.y -= (ImGui::GetFrameHeightWithSpacing() + ImGui::GetStyle().FrameBorderSize * 2);

			// draw a texture of the scene
			ImGui::Image((ImTextureID)(intptr_t)texId, size, ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));

			ImGui::End();
		}
	}

	void EditorSystem::GameObjectAddCallback(EventArgs& args)
	{
		/*GameObjectEventArgs* gameObjArgs = static_cast<GameObjectEventArgs*>(&args);
		GameObjectPtr obj = gameObjArgs->gameObj.lock();

		if (obj) // check it hasnt expired
		{
			CameraComponent* cam = obj->GetComponent<CameraComponent>();

			if (cam)
			{
				m_Camera = obj;
			}
		}*/
	}

	void EditorSystem::UpdateHierarchyTreeRecursive(GameObjectWeakPtr obj)
	{
		GameObjectPtr gameObj = obj.lock();

		// if gameobject has expired. we dont care here. let another system deal with that
		if (gameObj != nullptr)
		{
			if (gameObj->GetChildren().size() > 0)
			{
				if (ImGui::TreeNode(gameObj->GetName().c_str()))
				{
					for (GameObjectWeakPtr child : gameObj->GetChildren())
					{
						UpdateHierarchyTreeRecursive(child);
					}

					ImGui::TreePop();
				}
			}
			else
			{
				bool selected = false;
				ImGui::Selectable(gameObj->GetName().c_str(), selected);
			}
		}
	}
}