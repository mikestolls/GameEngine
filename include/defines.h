#pragma once

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>

#include <glm/glm.hpp>

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