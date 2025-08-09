#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

void Texture::loadImgTexture(string path)
{
	stbi_set_flip_vertically_on_load(false);
	if (m_data) {
		free(m_data);
	}
	m_data = stbi_load(path.c_str(), &m_width, &m_height, &m_channel, 0);
}

vec4 Texture::sample2DFromImg(vec2 texPos)
{
	float x = texPos.x - (float)floor(texPos.x);
	float y = texPos.y - (float)floor(texPos.y);
	return getOnePosColor(x * (m_width - 1), y * (m_height - 1)) / 255.0f;
}

vec4 Texture::getOnePosColor(int x, int y)
{
	int pos = (x + m_width * y) * 3;
	return vec4(*(m_data + pos + 0), *(m_data + pos + 1), *(m_data + pos + 2), 0);
}
