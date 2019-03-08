#pragma once
#include "defines.h"

namespace GameEngine
{
	class MaterialManager
	{
	public:

												MaterialManager();
												~MaterialManager();

		int										Initialize();
		int										Destroy();

	private:

	};

	typedef std::shared_ptr<MaterialManager>	MaterialManagerPtr;
}