#include "ui/ImguiDriver.h"
#include "rendering/Shader_OpenGL.h"
#include "Engine.h"

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

		int ImguiDriver::Initialize(void* handle, int screenWidth, int screenHeight, DriverPtr driver)
		{
			// initialize imgui
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();

			ImGuiIO& io = ImGui::GetIO();
			io.ImeWindowHandle = handle;
			io.DisplaySize = ImVec2((float)screenWidth, (float)screenHeight);
			io.DisplayFramebufferScale = ImVec2(screenWidth > 0 ? ((float)screenWidth / screenWidth) : 0, screenHeight > 0 ? ((float)screenHeight / screenHeight) : 0);

			// Setup Dear ImGui style
			ImGui::StyleColorsClassic();

			m_Material = Engine::GetInstance()->GetMaterialMgr()->CreateMaterial("imgui/imgui_material.mat");

			// create vao
			glGenVertexArrays(1, &m_VertexArrayId);
			glBindVertexArray(m_VertexArrayId);

			// create vbos and bind
			glGenBuffers(1, &m_VertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

			glGenBuffers(1, &m_IndexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

			glEnableVertexAttribArray(0); // position vec2
			glEnableVertexAttribArray(1); // uv vec2
			glEnableVertexAttribArray(2); // color vec4

			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)IM_OFFSETOF(ImDrawVert, pos));
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)IM_OFFSETOF(ImDrawVert, uv));
			glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(ImDrawVert), (GLvoid*)IM_OFFSETOF(ImDrawVert, col));

			// unbind
			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			// create the font texture
			unsigned char* pixels;
			int width, height;
			io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

			m_FontTexture = Engine::GetInstance()->GetTextureMgr()->CreateTexture("imgui_font", width, height, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

			// Store our identifier
			io.Fonts->TexID = (ImTextureID)(intptr_t)m_FontTexture->GetTextureId();

			// Restore state
			glBindTexture(GL_TEXTURE_2D, 0);

			// setup frame event callback
			Engine::GetInstance()->GetEventMgr()->RegisterEventListener("Frame_PreUpdate", std::bind(&ImguiDriver::PreUpdate, this));
			Engine::GetInstance()->GetEventMgr()->RegisterEventListener("Frame_PostUpdate", std::bind(&ImguiDriver::PostUpdate, this));

			return 0;
		}

		int ImguiDriver::Destroy()
		{
			if (m_VertexBuffer)
			{
				glDeleteBuffers(1, &m_VertexBuffer);
			}

			if (m_IndexBuffer)
			{
				glDeleteBuffers(1, &m_IndexBuffer);
			}

			if (m_VertexArrayId)
			{
				glDeleteVertexArrays(1, &m_VertexArrayId);
			}

			glDeleteVertexArrays = 0;
			m_VertexBuffer = 0;
			m_IndexBuffer = 0;

			m_Material = nullptr;
			m_FontTexture = nullptr;

			return 0;
		}

		void ImguiDriver::PreUpdate()
		{
			ImGuiIO& io = ImGui::GetIO();

			io.DeltaTime = Engine::GetInstance()->GetDeltaTime();
			
			ImGui::NewFrame();
		}

		void ImguiDriver::PostUpdate()
		{
			ImGui::Render();

			ImDrawData* drawData = ImGui::GetDrawData();

			// check we are rendering a non zero fb
			int fbWidth = (int)(drawData->DisplaySize.x * drawData->FramebufferScale.x);
			int fbHeight = (int)(drawData->DisplaySize.y * drawData->FramebufferScale.y);

			if (fbWidth <= 0 || fbHeight <= 0)
			{
				return;
			}

			// setup open gl state
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_FontTexture->GetTextureId());

			glEnable(GL_BLEND);
			glBlendEquation(GL_FUNC_ADD);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glDisable(GL_CULL_FACE);
			glDisable(GL_DEPTH_TEST);
			glEnable(GL_SCISSOR_TEST);
#ifdef GL_POLYGON_MODE
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#endif

			// setup viewport and ortho proj matrix
			glViewport(0, 0, (GLsizei)fbWidth, (GLsizei)fbHeight);
			glm::mat4 projMat = glm::ortho(0.0f, (float)fbWidth, (float)fbHeight, 0.0f);

			// activate material and set uniforms
			m_Material->SetActive(0);
			m_Material->GetShader(0)->SetUniformMat4("ProjMat", projMat);

			// activate and enable vb
			glBindVertexArray(m_VertexArrayId);

			// clipping
			ImVec2 clipOff = drawData->DisplayPos;
			ImVec2 clipScale = drawData->FramebufferScale;

			// Render command lists
			for (int n = 0; n < drawData->CmdListsCount; n++)
			{
				const ImDrawList* cmdList = drawData->CmdLists[n];
				size_t idxBufferOffset = 0;

				glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
				glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)cmdList->VtxBuffer.Size * sizeof(ImDrawVert), (const GLvoid*)cmdList->VtxBuffer.Data, GL_STREAM_DRAW);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)cmdList->IdxBuffer.Size * sizeof(ImDrawIdx), (const GLvoid*)cmdList->IdxBuffer.Data, GL_STREAM_DRAW);

				for (int cmd_i = 0; cmd_i < cmdList->CmdBuffer.Size; cmd_i++)
				{
					const ImDrawCmd* pcmd = &cmdList->CmdBuffer[cmd_i];

					if (pcmd->UserCallback)
					{
						// User callback (registered via ImDrawList::AddCallback)
						pcmd->UserCallback(cmdList, pcmd);
					}
					else
					{
						// Project scissor/clipping rectangles into framebuffer space
						ImVec4 clipRect;
						clipRect.x = (pcmd->ClipRect.x - clipOff.x) * clipScale.x;
						clipRect.y = (pcmd->ClipRect.y - clipOff.y) * clipScale.y;
						clipRect.z = (pcmd->ClipRect.z - clipOff.x) * clipScale.x;
						clipRect.w = (pcmd->ClipRect.w - clipOff.y) * clipScale.y;

						if (clipRect.x < fbWidth && clipRect.y < fbHeight && clipRect.z >= 0.0f && clipRect.w >= 0.0f)
						{
							// Apply scissor/clipping rectangle
							bool clipOriginLowerLeft = true;

							if (clipOriginLowerLeft)
							{
								glScissor((int)clipRect.x, (int)(fbHeight - clipRect.w), (int)(clipRect.z - clipRect.x), (int)(clipRect.w - clipRect.y));
							}
							else
							{
								glScissor((int)clipRect.x, (int)clipRect.y, (int)clipRect.z, (int)clipRect.w);
							}

							// Bind texture, Draw
							glBindTexture(GL_TEXTURE_2D, (GLuint)(intptr_t)pcmd->TextureId);
							glDrawElements(GL_TRIANGLES, (GLsizei)pcmd->ElemCount, sizeof(ImDrawIdx) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, (void*)idxBufferOffset);
						}
					}

					idxBufferOffset += pcmd->ElemCount * sizeof(ImDrawIdx);
				}
			}

			// clear down
			glUseProgram(0);
			glBindTexture(GL_TEXTURE_2D, 0);
			glBindVertexArray(0);
			glDisable(GL_SCISSOR_TEST);
			glDisable(GL_BLEND);
		}

		void ImguiDriver::UpdateMouseState(bool leftDown, bool middleDown, bool rightDown, int posX, int posY)
		{
			ImGuiIO& io = ImGui::GetIO();

			io.MouseDown[0] = leftDown;
			io.MouseDown[1] = middleDown;
			io.MouseDown[2] = rightDown;

			io.MousePos = ImVec2((float)posX, (float)posY);
		}
	}
}
