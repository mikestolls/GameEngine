#include "component/MeshComponent.h"

namespace GameEngine
{
	MeshComponent::MeshComponent() : IComponent()
	{
		m_Name = "Mesh Component";

		// test for now
		m_Mesh = std::make_shared<Mesh>("mesh/minifig.fbx");
	}

	MeshComponent::~MeshComponent()
	{

	}
}