#pragma once
#include "defines.h"

namespace GameEngine
{
	// putting interface here for now
	class IDriver
	{
	public:

		enum DRIVER_CLEAR
		{
			CLEAR_COLOR = 0x1,
			CLEAR_DEPTH = 0x2,
			CLEAR_STENCIL = 0x4,
		};

										IDriver() { }
										~IDriver() { }

		virtual int						Initialize() = 0;
		virtual int						Destroy() = 0;

		virtual int						PreUpdate() = 0;
		virtual int						PostUpdate() = 0;

		inline void						SetViewport(Math::Recti viewport) { m_ViewportRect = viewport; }
		inline void						SetViewport(glm::vec2 a, glm::vec2 b) { m_ViewportRect.a = a; m_ViewportRect.b = b; }

		void							SetClearColor(glm::vec4 color) { SetClearColor(color.r, color.g, color.b, color.a);	}
		virtual void					SetClearColor(float r, float g, float b, float a) = 0;

		virtual void					Clear(DRIVER_CLEAR clear) = 0;

	protected:
		
		Math::Recti						m_ViewportRect;
	};

	typedef std::shared_ptr<IDriver>	DriverPtr;

	class Driver_OpenGL : public IDriver
	{
	public:
										Driver_OpenGL();
										~Driver_OpenGL();

		int								Initialize();
		int								Destroy();

		int								PreUpdate();
		int								PostUpdate();

		void							SetClearColor(float r, float g, float b, float a);

		void							Clear(DRIVER_CLEAR clear);
	};
}