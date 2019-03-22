#include "rendering/Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Engine.h"

namespace GameEngine
{
	Mesh::Mesh(const char* meshFilename)
	{
		m_MeshFilename = meshFilename;

		ConstructScene();
	}

	Mesh::~Mesh()
	{
		m_MeshFilename.clear();

		glDeleteBuffers(1, &m_VertexBuffer);

		if (m_NormalBuffer != GL_INVALID_INDEX)
		{
			glDeleteBuffers(1, &m_NormalBuffer);
		}

		if (m_ColorBuffer != GL_INVALID_INDEX)
		{
			glDeleteBuffers(1, &m_ColorBuffer);
		}

		glDeleteVertexArrays(1, &m_VertexArrayID);

		glDeleteBuffers(1, &m_BoundingVertexBuffer);
		glDeleteVertexArrays(1, &m_BoundingVertexArrayID);

		m_Scene = NULL;
	}

	void Mesh::Render()
	{
		// calculate model matrix. all this is test for now
		glm::mat4 rotation = glm::mat4(1.0f);
		glm::mat4 translation = glm::translate(glm::vec3());
		glm::mat4 scale = glm::mat4(1.0f);

		glm::mat4 modelMat = translation * rotation * scale;
		glm::mat4 projMat = glm::perspective(1136.0f / 640.0f, glm::radians(45.0f), 0.1f, 2000.0f);
		glm::mat4 viewMat = glm::lookAt(glm::vec3(0.0f, 0.0f, -100.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		
		glBindVertexArray(m_VertexArrayID);

		for (unsigned int i = 0; i < m_Material->GetNumPasses(); i++)
		{
			if (m_Material->GetShader(i) == nullptr)
			{
				continue;
			}

			m_Material->SetActive(i);
			m_Material->GetShader(i)->SetUniformMat4("ProjMat", projMat);
			m_Material->GetShader(i)->SetUniformMat4("ModelMat", modelMat);
			m_Material->GetShader(i)->SetUniformMat4("ViewMat", viewMat);
			
			// Draw the triangle !
			glDrawArrays(GL_TRIANGLES, 0, m_VertexCount);
		}

		glBindVertexArray(0);

		// bounding box draw
		/*if (m_BoundingBoxVisible)
		{
			// draw bounding box	
			m_BoundingShader->SetActive();
			m_BoundingShader->SetUniformMat4("ModelMatrix", translation);

			glBindVertexArray(m_BoundingVertexArrayID);
			glEnableVertexAttribArray(0);

			glDrawArrays(GL_LINE_LOOP, 0, 4);
			glDrawArrays(GL_LINE_LOOP, 4, 4);
			glDrawArrays(GL_LINES, 8, 8);

			glDisableVertexAttribArray(0);
			glBindVertexArray(0);
		}*/
	}

	void Mesh::ConstructScene()
	{
		m_Scene = m_Importer.ReadFile(m_MeshFilename.c_str(), aiProcess_Triangulate | aiProcess_PreTransformVertices);

		// construct vertex buffers
		std::vector< glm::vec3 > vertices;
		std::vector< glm::vec3 > normals;
		std::vector< glm::vec3 > colors;
		std::vector< glm::vec2 > uvs;

		// calculate the bounding box
		m_BoundingMin.x = FLT_MAX;
		m_BoundingMin.y = FLT_MAX;
		m_BoundingMin.z = FLT_MAX;
		m_BoundingMax.x = 0;
		m_BoundingMax.y = 0;
		m_BoundingMax.z = 0;

		m_BoundingBoxVisible = false;

		RecursiveChildren(m_Scene->mRootNode, vertices, normals, colors, uvs);

		m_VertexCount = (unsigned int)vertices.size();

		// construct vertex array id along with buffers
		glGenVertexArrays(1, &m_VertexArrayID);
		glBindVertexArray(m_VertexArrayID);

		if (vertices.size() > 0)
		{
			glGenBuffers(1, &m_VertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(
				0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				3 * sizeof(float),                  // stride
				(void*)0            // array buffer offset
			);
		}

		if (normals.size() > 0)
		{
			glGenBuffers(1, &m_NormalBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, m_NormalBuffer);
			glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(
				1,                  // attribute 1. No particular reason for 1, but must match the layout in the shader.
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				3 * sizeof(float),                  // stride
				(void*)0            // array buffer offset
			);
		}
		else
		{
			m_NormalBuffer = GL_INVALID_INDEX;
			glDisableVertexAttribArray(1);
		}

		if (colors.size() > 0)
		{
			glGenBuffers(1, &m_ColorBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer);
			glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), &colors[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(
				2,                  // attribute 1. No particular reason for 1, but must match the layout in the shader.
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				3 * sizeof(float),                  // stride
				(void*)0            // array buffer offset
			);
		}
		else
		{
			m_ColorBuffer = GL_INVALID_INDEX;
			glDisableVertexAttribArray(2);
		}

		// unbinned array id
		glBindVertexArray(0);

		// create a bounding box
		float bbVertices[] = {
			// back
			m_BoundingMin.x, m_BoundingMin.y, m_BoundingMin.z,
			m_BoundingMin.x, m_BoundingMax.y, m_BoundingMin.z,
			m_BoundingMax.x, m_BoundingMax.y, m_BoundingMin.z,
			m_BoundingMax.x, m_BoundingMin.y, m_BoundingMin.z,
			//front
			m_BoundingMin.x, m_BoundingMin.y, m_BoundingMax.z,
			m_BoundingMin.x, m_BoundingMax.y, m_BoundingMax.z,
			m_BoundingMax.x, m_BoundingMax.y, m_BoundingMax.z,
			m_BoundingMax.x, m_BoundingMin.y, m_BoundingMax.z,
			//side
			m_BoundingMin.x, m_BoundingMin.y, m_BoundingMin.z,
			m_BoundingMin.x, m_BoundingMin.y, m_BoundingMax.z,
			m_BoundingMin.x, m_BoundingMax.y, m_BoundingMin.z,
			m_BoundingMin.x, m_BoundingMax.y, m_BoundingMax.z,
			m_BoundingMax.x, m_BoundingMax.y, m_BoundingMin.z,
			m_BoundingMax.x, m_BoundingMax.y, m_BoundingMax.z,
			m_BoundingMax.x, m_BoundingMin.y, m_BoundingMin.z,
			m_BoundingMax.x, m_BoundingMin.y, m_BoundingMax.z,
		};

		// generate and bind vertex array
		glGenVertexArrays(1, &m_BoundingVertexArrayID);
		glBindVertexArray(m_BoundingVertexArrayID);

		glGenBuffers(1, &m_BoundingVertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_BoundingVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(bbVertices), bbVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
			0,                  // attribute 1. No particular reason for 1, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			3 * sizeof(float),                  // stride
			(void*)0            // array buffer offset
		);

		glBindVertexArray(0);

		// create material
		m_Material = Engine::GetInstance()->GetMaterialMgr()->CreateMaterial("material/mesh_material.mat");
	}

	void Mesh::RecursiveChildren(aiNode* node, std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals, std::vector<glm::vec3>& colors, std::vector<glm::vec2>& uvs)
	{
		for (unsigned int x = 0; x < node->mNumMeshes; x++)
		{
			const struct aiMesh* mesh = m_Scene->mMeshes[node->mMeshes[x]];

			for (unsigned int t = 0; t < mesh->mNumFaces; ++t)
			{
				const struct aiFace* face = &mesh->mFaces[t];

				assert(face->mNumIndices == 3); // only supprot triangles

				for (unsigned int i = 0; i < face->mNumIndices; i++)		// go through all vertices in face
				{
					int vertexIndex = face->mIndices[i];	// get group index for current index
					aiVector3D pos = mesh->mVertices[vertexIndex];
					aiVector3D norm = mesh->mNormals[vertexIndex];

					if (pos.x < m_BoundingMin.x) m_BoundingMin.x = pos.x;
					if (pos.x > m_BoundingMax.x) m_BoundingMax.x = pos.x;
					if (pos.y < m_BoundingMin.y) m_BoundingMin.y = pos.y;
					if (pos.y > m_BoundingMax.y) m_BoundingMax.y = pos.y;
					if (pos.z < m_BoundingMin.z) m_BoundingMin.z = pos.z;
					if (pos.z > m_BoundingMax.z) m_BoundingMax.z = pos.z;

					vertices.push_back(glm::vec3(pos.x, pos.y, pos.z));
					normals.push_back(glm::vec3(norm.x, norm.y, norm.z));

					if (mesh->mColors[0] != NULL)
					{
						colors.push_back(glm::vec3(mesh->mColors[0][vertexIndex].r, mesh->mColors[0][vertexIndex].g, mesh->mColors[0][vertexIndex].b));
					}
				}
			}
		}

		for (unsigned int i = 0; i < node->mNumChildren; ++i)
		{
			RecursiveChildren(node->mChildren[i], vertices, normals, colors, uvs);
		}
	}
}