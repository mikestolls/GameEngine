#include "rendering/Mesh.h"

namespace GameEngine
{
	Mesh::Mesh(const char* meshFilename)
	{
		m_MeshFilename = meshFilename;
	}

	Mesh::~Mesh()
	{
		m_MeshFilename.clear();
	}
}