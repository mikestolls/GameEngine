#include "ui/ImguiDriver.h"

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

			return 0;
		}

		int ImguiDriver::Destroy()
		{
			return 0;
		}
	}
}
