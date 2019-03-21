#pragma once
#include "defines.h"

namespace GameEngine
{
	class Mesh
	{
	public:

											Mesh(const char* meshFilename);
											~Mesh();
											
	private:

		std::string							m_MeshFilename;
	};

	typedef std::shared_ptr<Mesh>			MeshPtr;
}