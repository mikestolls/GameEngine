#pragma once
#include "defines.h"

#include "rendering/Material.h"

namespace GameEngine
{
	class MaterialManager
	{
	public:

												MaterialManager();
												~MaterialManager();

		int										Initialize();
		int										Destroy();

		MaterialPtr								CreateMaterial(const char* materialFilename);

	private:

	};

	typedef std::shared_ptr<MaterialManager>	MaterialManagerPtr;
}