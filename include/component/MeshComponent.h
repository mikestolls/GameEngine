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

		inline MeshPtr						GetMesh() { return m_Mesh; }

	private:

		MeshPtr								m_Mesh;
	};
}