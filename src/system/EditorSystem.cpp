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

		Engine::GetInstance()->GetEventMgr()->RegisterEventListener("GameObject_Add", std::bind(&EditorSystem::GameObjectAddCallback, this, std::placeholders::_1));

		return 0;
	}

	int EditorSystem::Destroy()
	{
		return 0;
	}

	void EditorSystem::Update()
	{
		int ret = 0;

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				ImGui::MenuItem("New Scene");
				ImGui::MenuItem("Open Scene");
				if (ImGui::MenuItem("Exit"))
				{
					Engine::GetInstance()->GetEventMgr()->SendEvent("Platform_Shutdown");
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Game Object"))
			{
				ImGui::MenuItem("New Game Object");

				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
		
		// start test
		ImGui::Begin("Hello, world!");

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
		}
		// end test
	}

	void EditorSystem::GameObjectAddCallback(EventArgs& args)
	{
		GameObjectEventArgs* gameObjArgs = static_cast<GameObjectEventArgs*>(&args);
		GameObjectPtr obj = gameObjArgs->gameObj.lock();

		if (obj) // check it hasnt expired
		{
			CameraComponent* cam = obj->GetComponent<CameraComponent>();

			if (cam)
			{
				m_Camera = obj;
			}
		}
	}

}