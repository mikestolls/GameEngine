#pragma once
#include "manager/GameObjectManager.h"
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