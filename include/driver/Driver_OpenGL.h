#pragma once
#include "defines.h"

namespace GameEngine
{
	// putting interface here for now
	class IDriver
	{
	public:

		enum
		{
			CLEAR_COLOR = 0x1,
			CLEAR_DEPTH = 0x2,
			CLEAR_STENCIL = 0x4,
		};

										IDriver() { }
										~IDriver() { }

		virtual int						Initialize() = 0;
		virtual int						Destroy() = 0;

		virtual void					PreUpdate() = 0;
		virtual void					PostUpdate() = 0;

		inline void						SetViewport(Math::Recti viewport) { m_ViewportRect = viewport; }
		inline void						SetViewport(glm::vec2 a, glm::vec2 b) { m_ViewportRect.a = a; m_ViewportRect.b = b; }

		void							SetClearColor(glm::vec4 color) { SetClearColor(color.r, color.g, color.b, color.a);	}
		virtual void					SetClearColor(float r, float g, float b, float a) = 0;

		virtual void					Clear(int clear) = 0;

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

		void							PreUpdate();
		void							PostUpdate();

		void							SetClearColor(float r, float g, float b, float a);

		void							Clear(int clear);
	};
}