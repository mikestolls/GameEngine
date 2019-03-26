#pragma once
#include "defines.h"
#include "Shader_OpenGL.h"

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

namespace GameEngine
{
	struct MaterialPass
	{
		ShaderPtr shader;
		std::vector<ShaderUniform> shaderUniforms;
	};

	class Material
	{
	public:

											Material(const char* materialFilename);
											~Material();

		void								SetActive(unsigned int passIndex);

		inline unsigned int					GetNumPasses() { return (unsigned int)m_MaterialPasses.size(); }
		inline ShaderPtr					GetShader(unsigned int passIndex) { return m_MaterialPasses[passIndex].shader; }

	private:

		void								Recompile();
		MaterialPass						ParseMaterialPass(const rapidjson::Value& pass);

		std::string							m_MaterialFilename;

		std::vector<MaterialPass>			m_MaterialPasses;
	};

	typedef std::shared_ptr<Material>		MaterialPtr;
}