#pragma once
#include "defines.h"
#include "driver/Driver_OpenGL.h"
#include "rendering/Material.h"
#include "rendering/Texture_OpenGL.h"
#include "manager/MaterialManager.h"

namespace GameEngine
{
	namespace UI
	{
		class ImguiDriver
		{
		public:

												ImguiDriver();
												~ImguiDriver();

			int									Initialize(void* handle, int screenWidth, int screenHeight, DriverPtr driver);
			int									Destroy();

			int									Update(float dt);
			int									Render();

		private:

			DriverPtr							m_Driver;
			MaterialPtr							m_Material;
			TexturePtr							m_FontTexture;

			unsigned int						m_VertexArrayId;
			unsigned int						m_VertexBuffer;
			unsigned int						m_IndexBuffer;

			int									m_AttribLocationPosition;
			int									m_AttribLocationUV; 
			int									m_AttribLocationColor;
		};

		typedef std::shared_ptr<ImguiDriver>	ImguiDriverPtr;
	}
}