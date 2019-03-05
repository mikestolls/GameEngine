#include "defines.h"
#include "platform/Platform_Windows.h"
#include "Engine.h"

// Include GLEW. Always include it before gl.h and glfw.h, since it's a bit magic.
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace GameEngine
{
	GLFWwindow* window; // (In the accompanying source code, this variable is global)

	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mod);
	void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	void MouseCallback(GLFWwindow* window, double xpos, double ypos);

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

		glfwMakeContextCurrent(window); // Initialize GLEW

		// Set the required callback functions
		glfwSetKeyCallback(window, KeyCallback);
		glfwSetCursorPosCallback(window, MouseCallback);
		glfwSetScrollCallback(window, ScrollCallback);

		// Options
		glfwSetInputMode(window, GLFW_CURSOR, GL_TRUE);

		glewExperimental = true; // Needed in core profile
		if (glewInit() != GLEW_OK)
		{
			fprintf(stderr, "Failed to initialize GLEW\n");
			return -1;
		}

		// Ensure we can capture the escape key being pressed below
		glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

		m_Driver = std::make_shared<Driver_OpenGL>();
		m_Driver->Initialize();

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

		while (!glfwWindowShouldClose(window))
		{
			// Check and call events
			glfwPollEvents();

			m_Driver->PreUpdate();

			// engine update
			engine->Update(0.0f);

			m_Driver->PostUpdate();

			// Swap buffers
			glfwSwapBuffers(window);
		}

		engine->Destroy();
		Destroy();

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

	void MouseCallback(GLFWwindow* window, double xpos, double ypos)
	{

	}
}

int main(const int argc, const char* argv[])
{
	GameEngine::Platform_Windows platform("Game Engine", 1136, 640);

	platform.Run();
}