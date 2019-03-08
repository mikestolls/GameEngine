#include "ui/ImguiDriver.h"
#include "rendering/Shader_OpenGL.h"

#include "imgui.h"

namespace GameEngine
{
	namespace UI
	{
		ImguiDriver::ImguiDriver()
		{

		}

		ImguiDriver::~ImguiDriver()
		{

		}

		int ImguiDriver::Initialize(void* handle, DriverPtr driver)
		{
			// initialize imgui
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();

			io.ImeWindowHandle = handle;

			// Setup Dear ImGui style
			ImGui::StyleColorsDark();

			ShaderPtr shader = std::make_shared<Shader_OpenGL>("imgui_vertex.glsl", "imgui_fragment.glsl", "");

			return 0;
		}

		int ImguiDriver::Destroy()
		{
			return 0;
		}
	}
}
