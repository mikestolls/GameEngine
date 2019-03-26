#pragma once
#include "defines.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <rendering/Material.h>

namespace GameEngine
{
	class Mesh
	{
	public:

											Mesh(const char* meshFilename);
											~Mesh();
											
		void								Render();

	private:

		void								ConstructScene();
		void								RecursiveChildren(aiNode* node, std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals, std::vector<glm::vec3>& colors, std::vector<glm::vec2>& uvs);

		std::string							m_MeshFilename;

		unsigned int						m_VertexArrayID;

		unsigned int						m_VertexBuffer;
		unsigned int						m_NormalBuffer;
		unsigned int						m_ColorBuffer;

		unsigned int						m_VertexCount;

		unsigned int						m_BoundingVertexArrayID;

		unsigned int						m_BoundingVertexBuffer;
		unsigned int						m_BoundingElementBuffer;

		bool								m_BoundingBoxVisible;
		glm::vec3							m_BoundingMin;
		glm::vec3							m_BoundingMax;

		Assimp::Importer					m_Importer;
		const aiScene*						m_Scene;

		MaterialPtr							m_Material;
	};

	typedef std::shared_ptr<Mesh>			MeshPtr;
}