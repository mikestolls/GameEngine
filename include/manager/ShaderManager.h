#pragma once
#include "defines.h"

namespace GameEngine
{
	class ShaderManager
	{
	public:

											ShaderManager();
											~ShaderManager();

		int									Initialize();
		int									Destroy();

	private:

	};

	typedef std::shared_ptr<ShaderManager>	ShaderManagerPtr;
}