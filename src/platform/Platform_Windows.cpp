#include "defines.h"
#include "platform/Platform_Windows.h"
#include "Engine.h"

#include "imgui.h"

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

		glfwMakeContextCurrent(window);
		glfwSwapInterval(1); // Enable vsync
				
		if (gl3wInit() != 0)
		{
			fprintf(stderr, "Failed to initialize OpenGL loader!\n");
			return 1;
		}

		// Set the required callback functions
		glfwSetKeyCallback(window, KeyCallback);
		glfwSetCursorPosCallback(window, MouseCallback);
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

		// start of test
		/*
		float halfWidth = (float)m_ScreenWidth * 0.5f;
		float halfHeight = (float)m_ScreenHeight * 0.5f;
		glm::mat4 projMat = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight);
		MaterialPtr mat = Engine::GetInstance()->GetMaterialMgr()->CreateMaterial("imgui/imgui_material.mat");
		mat->SetActive(0);

		float vertices[] = {
			-100.0f, -100.0f,
			100.0f, -100.0f,
			0.0f,  100.0f,
		};

		GLuint vbo;
		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo); // Generate 1 buffer
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			2,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		*/
		// end of test

		bool show_demo_window = true;
		while (!glfwWindowShouldClose(window))
		{
			// Set frame time
			float currentFrame = static_cast<float>(glfwGetTime());
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			glfwPollEvents();

			//m_Driver->PreUpdate();

			// start of test 
			/*
			mat->SetActive(0);
			mat->GetShader(0)->SetUniformMat4("ProjMat", projMat);

			glBindVertexArray(vao);
			
			// Draw the triangle !
			glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

			glBindVertexArray(0);
			*/
			// end of test

			// engine update
			//engine->Update(deltaTime);
			m_ImguiDriver->Update(deltaTime);

			//m_Driver->PostUpdate();

			// test rendering some elements
			ImGui::NewFrame();

			ImGui::Begin("Hello, world!");
			ImGui::End();

			// end test

			/*ImGui::Render();
			ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
			int display_w, display_h;
			glfwMakeContextCurrent(window);
			glfwGetFramebufferSize(window, &display_w, &display_h);
			glViewport(0, 0, display_w, display_h);
			glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
			glClear(GL_COLOR_BUFFER_BIT);*/

			m_ImguiDriver->Render();

			// Swap buffers
			glfwMakeContextCurrent(window);
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