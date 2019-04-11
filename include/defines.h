#pragma once

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <forward_list>
#include <unordered_map>
#include <fstream>
#include <functional>

// Include GLEW. Always include it before gl.h and glfw.h, since it's a bit magic.
#include <GL/gl3w.h>
#include "GLFW/glfw3.h"

#ifdef _WIN32
#undef APIENTRY
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>   // for glfwGetWin32Window
#endif

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace GameEngine
{
	namespace Math
	{
		template <typename T>
		struct Rect
		{
			glm::tvec2<T> a;
			glm::tvec2<T> b;
		};

		typedef Rect<int>		Recti;
		typedef Rect<float>		Rectf;
	}
}