#pragma once
#include "system/GameObjectSystem.h"
#include "rendering/Mesh.h"

namespace GameEngine
{
	class MeshComponent : public IComponent
	{
	public:
											MeshComponent();
											~MeshComponent();

	private:

		MeshPtr								m_Mesh;
	};
}