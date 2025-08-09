#pragma once
#include "globel.h"

namespace SoftRender
{
	class Texture {
	public:
		Texture() : m_width(0), m_height(0), m_channel(0), m_data(nullptr) {}
		Texture(string path) {
			m_width = 0, m_height = 0, m_channel = 0, m_data = nullptr;
			loadImgTexture(path);
		}
		Texture& operator=(const Texture& t) {
			m_width = t.m_width;
			m_height = t.m_height;
			m_channel = t.m_channel;
			if (t.m_data) {
				m_data = (unsigned char*)malloc(m_width * m_height * m_channel);
				memcpy(m_data, t.m_data, m_width * m_height * m_channel);
			}
			return *this;
		}

		~Texture() = default;

		void loadImgTexture(string path);
		vec4 sample2DFromImg(vec2 texPos);
		vec4 getOnePosColor(int x, int y);

	public:
		int m_width;
		int m_height;
		int m_channel;
		string m_path;
		unsigned char* m_data;
	};
}