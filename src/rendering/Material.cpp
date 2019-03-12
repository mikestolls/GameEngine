#include "rendering/Material.h"
#include "manager/MaterialManager.h"
#include "Engine.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace GameEngine
{
	Material::Material(const char* materialFilename)
	{
		m_MaterialFilename = materialFilename;

		Recompile();
	}

	Material::~Material()
	{
		m_MaterialFilename.clear();
	}

	void Material::SetActive(unsigned int passIndex)
	{
		if (passIndex >= m_MaterialPasses.size())
		{
			return;
		}

		MaterialPass pass = m_MaterialPasses[passIndex];

		if (pass.shader == nullptr)
		{
			return;
		}

		pass.shader->SetActive();

		// set the uniforms saved to the mesh
		for (auto itr = pass.shaderUniforms.begin(); itr != pass.shaderUniforms.end(); itr++)
		{
			switch (itr->type)
			{
			case UniformType::Int:
				pass.shader->SetUniformInt1(itr->name.c_str(), itr->valueInt);
				break;
			case UniformType::Float:
				pass.shader->SetUniformFloat1(itr->name.c_str(), itr->valueFloat);
				break;
			case UniformType::Vec2:
				pass.shader->SetUniformVec2(itr->name.c_str(), itr->valueVec2);
				break;
			case UniformType::Vec3:
				pass.shader->SetUniformVec3(itr->name.c_str(), itr->valueVec3);
				break;
			case UniformType::Vec4:
				pass.shader->SetUniformVec4(itr->name.c_str(), itr->valueVec4);
				break;
			case UniformType::Mat3:
				pass.shader->SetUniformMat3(itr->name.c_str(), itr->valueMat3);
				break;
			case UniformType::Mat4:
				pass.shader->SetUniformMat4(itr->name.c_str(), itr->valueMat4);
				break;
			}
		}
	}

	void Material::Recompile()
	{
		std::ifstream inStream(m_MaterialFilename.c_str(), std::ios::in);
		if (!inStream.is_open())
		{
			printf("Error opening material\n");
			return;
		}

		rapidjson::IStreamWrapper streamWrapper(inStream);

		rapidjson::Document json;
		json.ParseStream(streamWrapper);

		if (!json.IsObject())
		{
			inStream.close();
			assert(0);
			return;
		}

		if (!json.HasMember("passes"))
		{
			m_MaterialPasses.clear();
			m_MaterialPasses.push_back(ParseMaterialPass(json));
		}
		else
		{
			const rapidjson::Value& passes = json["passes"];

			if (!passes.IsArray())
			{
				inStream.close();
				assert(0);
				return;
			}

			m_MaterialPasses.clear();
			for (unsigned int i = 0; i < passes.Size(); i++)
			{
				m_MaterialPasses.push_back(ParseMaterialPass(passes[i]));
			}
		}

		inStream.close();
	}

	MaterialPass Material::ParseMaterialPass(const rapidjson::Value& pass)
	{
		std::string vertFilename = pass["vertex_shader"].GetString();
		std::string fragFilename = pass["fragment_shader"].GetString();
		std::string shaderDefines = pass["shader_defines"].GetString();
		const rapidjson::Value& uniforms = pass["uniforms"];

		if (!uniforms.IsArray())
		{
			assert(0);
			return MaterialPass();
		}

		MaterialPass matPass;
		for (unsigned int j = 0; j < uniforms.Size(); j++)
		{
			ShaderUniform uniform;

			if (strcmp(uniforms[j]["type"].GetString(), "float") == 0)
			{
				uniform.type = UniformType::Float;
				uniform.valueFloat = uniforms[j]["value"].GetFloat();
			}
			else if (strcmp(uniforms[j]["type"].GetString(), "int") == 0)
			{
				uniform.type = UniformType::Int;
				uniform.valueInt = uniforms[j]["value"].GetInt();
			}
			else if (strcmp(uniforms[j]["type"].GetString(), "vec2") == 0)
			{
				uniform.type = UniformType::Vec2;
				uniform.valueVec2 = glm::vec2(uniforms[j]["value_x"].GetFloat(), uniforms[j]["value_y"].GetFloat());
			}
			else if (strcmp(uniforms[j]["type"].GetString(), "vec3") == 0)
			{
				uniform.type = UniformType::Vec3;
				uniform.valueVec3 = glm::vec3(uniforms[j]["value_x"].GetFloat(), uniforms[j]["value_y"].GetFloat(), uniforms[j]["value_z"].GetFloat());
			}
			else if (strcmp(uniforms[j]["type"].GetString(), "vec4") == 0)
			{
				uniform.type = UniformType::Vec4;
				uniform.valueVec4 = glm::vec4(uniforms[j]["value_x"].GetFloat(), uniforms[j]["value_y"].GetFloat(), uniforms[j]["value_z"].GetFloat(), uniforms[j]["value_w"].GetFloat());
			}

			uniform.name = uniforms[j]["name"].GetString();

			matPass.shaderUniforms.push_back(uniform);
		}

		matPass.shader = Engine::GetInstance()->GetShaderMgr()->CreateShader(vertFilename.c_str(), fragFilename.c_str(), shaderDefines.c_str());
		matPass.shader->Recompile();

		return matPass;
	}
}