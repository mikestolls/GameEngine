#include "manager/MaterialManager.h"

namespace GameEngine
{
	MaterialManager::MaterialManager()
	{

	}

	MaterialManager::~MaterialManager()
	{

	}

	int MaterialManager::Initialize()
	{
		return 0;
	}

	int MaterialManager::Destroy()
	{
		return 0;
	}

	MaterialPtr MaterialManager::CreateMaterial(const char* materialFilename)
	{
		return MaterialPtr(new Material(materialFilename));
	}
}