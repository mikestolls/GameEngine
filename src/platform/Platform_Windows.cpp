#include "defines.h"
#include "platform/Platform_Windows.h"
#include "Engine.h"

#include "imgui.h"

namespace GameEngine
{
	GLFWwindow* window; // (In the accompanying source code, this variable is global)

	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mod);
	void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	void MouseCallback(GLFWwindow* window, int button, int action, int mods);

	bool mousePressed[3] = { false, false, false };
	double mouseX, mouseY;

	Platform_Windows::Platform_Windows(const char* windowName, int screenWidth, int screenHeight)
	{
		m_WindowName = windowName;
		m_ScreenWidth = screenWidth;
		m_ScreenHeight = screenHeight;
	}

	Platform_Windows::~Platform_Windows()
	{

	}

	int Platform_Windows::Initialize()
	{
		if (!glfwInit())
		{
			fprintf(stderr, "Failed to initialize GLFW\n");
			return -1;
		}

		glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

		window = glfwCreateWindow(m_ScreenWidth, m_ScreenHeight, m_WindowName.c_str(), NULL, NULL);
		if (window == NULL)
		{
			fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
			glfwTerminate();
			return -1;
		}

		glfwMakeContextCurrent(window);
		glfwSwapInterval(1); // Enable vsync
				
		if (gl3wInit() != 0)
		{
			fprintf(stderr, "Failed to initialize OpenGL loader!\n");
			return 1;
		}

		// Set the required callback functions
		glfwSetKeyCallback(window, KeyCallback);
		glfwSetMouseButtonCallback(window, MouseCallback);
		glfwSetScrollCallback(window, ScrollCallback);

		// Options
		glfwSetInputMode(window, GLFW_CURSOR, GL_TRUE);
		
		// Ensure we can capture the escape key being pressed below
		glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

		m_Driver = std::make_shared<Driver_OpenGL>();
		m_Driver->Initialize();

		m_ImguiDriver = std::make_shared<GameEngine::UI::ImguiDriver>();
		m_ImguiDriver->Initialize((void*)glfwGetWin32Window(window), m_ScreenWidth, m_ScreenHeight, m_Driver);

		return 0;
	}

	int Platform_Windows::Destroy()
	{
		m_Driver->Destroy();
		m_Driver = nullptr;

		// Close OpenGL window and terminate GLFW
		glfwTerminate();

		return 0;
	}

	int Platform_Windows::Run()
	{
		Initialize();

		Engine* engine = Engine::GetInstance();
		engine->Initialize(m_Driver);

		float deltaTime = 0.0f;
		float lastFrame = 0.0f;

		float f = 0.0f;
		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		while (!glfwWindowShouldClose(window))
		{
			// Set frame time
			float currentFrame = static_cast<float>(glfwGetTime());
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			// poll and update inputs
			glfwPollEvents();
			UpdateMouse();

			m_Driver->PreUpdate();
			m_ImguiDriver->PreUpdate(deltaTime);

			// engine update
			engine->Update(deltaTime);

			// start test
			ImGui::Begin("Hello, world!");

			ImGui::SetWindowSize(ImVec2(300, 150));

			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
			ImGui::Checkbox("Another Window", &show_another_window);

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			ImGui::End();

			glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
			// end test


			m_Driver->PostUpdate();
			m_ImguiDriver->PostUpdate();

			// Swap buffers
			glfwMakeContextCurrent(window);
			glfwSwapBuffers(window);
		}

		engine->Destroy();
		Destroy();

		return 0;
	}

	int Platform_Windows::UpdateMouse()
	{
		// update imgui input
		const bool focused = glfwGetWindowAttrib(window, GLFW_FOCUSED) != 0;

		if (focused)
		{
			glfwGetCursorPos(window, &mouseX, &mouseY);

			m_ImguiDriver->UpdateMouseState(mousePressed[0] || glfwGetMouseButton(window, 0), mousePressed[1] || glfwGetMouseButton(window, 1), mousePressed[2] || glfwGetMouseButton(window, 2), (int)mouseX, (int)mouseY);

			mousePressed[0] = false;
			mousePressed[1] = false;
			mousePressed[2] = false;
		}

		return 0;
	}

	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mod)
	{
		if (key == -1)
		{
			return;
		}

		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}

	void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{

	}

	void MouseCallback(GLFWwindow* window, int button, int action, int mods)
	{
		if (action == GLFW_PRESS && button >= 0 && button < 3)
		{
			mousePressed[0] = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
			mousePressed[1] = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE);
			mousePressed[2] = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
		}
	}
}

int main(const int argc, const char* argv[])
{
	GameEngine::Platform_Windows platform("Game Engine", 1136, 640);

	platform.Run();
}