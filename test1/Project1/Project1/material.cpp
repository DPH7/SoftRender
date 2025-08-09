#include "material.h"

void Material::setAlbedoUV(string path, vec3 color)
{
	m_albedo = Texture(path);
	m_color = color;
}

void Material::setMetallicUV(string path, float num)
{
	m_metallic = Texture(path);
	m_smooth_num = num;
}

void Material::setNormalUV(string path)
{
	m_albedo = Texture(path);
}

void Material::setHeightUV(string path, float num)
{
	m_height = Texture(path);
	m_height_num = num;
}

void Material::setOcclusionUV(string path, float num)
{
	m_occlusion = Texture(path);
	m_ao_num = num;
}

void Material::setRoghnessUV(string path, float num)
{
	m_roghness = Texture(path);
	m_roghness_num = num;
}

glm::vec4 Material::sampleFromUV(MatType type, const glm::vec2& texcoord)
{
	if (type == MatType::ALBEDO) {
		return m_albedo.sample2DFromImg(texcoord);
	}
	else if(type == MatType::METALLIC) {
		return m_metallic.sample2DFromImg(texcoord);
	}
	else if (type == MatType::NORMAL) {
		return m_normal.sample2DFromImg(texcoord);
	}
	else if (type == MatType::HEIGHT) {
		return m_height.sample2DFromImg(texcoord);
	}
	else if (type == MatType::OCCLUSION) {
		return m_occlusion.sample2DFromImg(texcoord);
	}
	else if (type == MatType::ROUGHNESS) {
		return m_roghness.sample2DFromImg(texcoord);
	}

	return glm::vec4();
}

void Material::setVertexShader(VertexShaderBasic* _shader)
{
	m_vertexShader = _shader;
}

void Material::setFragmentShader(FragmentShaderBasic* _shader)
{
	m_fragmentShader = _shader;
}
