#pragma once
#include "glm/glm.hpp"
#include "texture.h"
#include "globel.h"
#include "fragment_shader_basic.h"
#include "vertex_shader_basic.h"

namespace SoftRender
{
	class Texture;
	class VertexShaderBasic;
	class FragmentShaderBasic;
	class Material {
	public:
		Material() :
			m_albedo(Texture()),
			m_color(vec3(255, 255, 255)),
			m_metallic(Texture()),
			m_smooth_num(0),
			m_normal(Texture()),
			m_height(Texture()),
			m_height_num(0),
			m_occlusion(Texture()),
			m_ao_num(0),
			m_roghness(Texture()),
			m_roghness_num(0)
		{
		}
		~Material() = default;

		void setAlbedoUV(string path, vec3 color = vec3(255, 255, 255));

		void setMetallicUV(string path, float num = 0.1);

		void setNormalUV(string path);

		void setHeightUV(string path, float num = 0);

		void setOcclusionUV(string path, float num = 0);

		void setRoghnessUV(string path, float num = 0);

		glm::vec4 sampleFromUV(MatType type, const glm::vec2& texcoord);

		void setVertexShader(VertexShaderBasic* _shader);
		void setFragmentShader(FragmentShaderBasic* _shader);

	public:
		Texture m_albedo;
		glm::vec3 m_color;

		Texture m_metallic;
		float m_smooth_num;

		Texture m_normal;

		Texture m_height;
		float m_height_num;

		Texture m_occlusion;
		float m_ao_num;

		Texture m_roghness;
		float m_roghness_num;

		VertexShaderBasic* m_vertexShader;
		FragmentShaderBasic* m_fragmentShader;
	};
}
