#include "frame_buffer.h"

namespace SoftRender {
	void FrameBuffer::initialize(window_info windowInfo)
	{
		m_buffer.resize(windowInfo.width * windowInfo.height * 4, 0);
		m_depth.resize(windowInfo.width * windowInfo.height, 1);
		m_width = windowInfo.width;
		m_height = windowInfo.height;
	}

	void FrameBuffer::clearBuffer(glm::vec4 color)
	{
		for (int i = 0; i < m_width * m_height * 4; i += 4)
		{
			m_buffer[i] = color.r * 255;
			m_buffer[i + 1] = color.g * 255;
			m_buffer[i + 2] = color.b * 255;
			m_buffer[i + 3] = color.a * 255;
		}

		m_depth.assign(m_width * m_height, 1.0f);
	}

	void FrameBuffer::drawOnePos(glm::vec3 pos, glm::vec4 color)
	{
		if (pos.x < 0 || pos.x >= m_width || pos.y < 0 || pos.y >= m_height)
			return;
		int posIdx = pos.y * m_width + pos.x;
		m_buffer[posIdx * 4] = color.r * 255;
		m_buffer[posIdx * 4 + 1] = color.g * 255;
		m_buffer[posIdx * 4 + 2] = color.b * 255;
		m_buffer[posIdx * 4 + 3] = color.a * 255;

		//…Ó∂»
		*(m_depth.data() + int(pos.y * m_width + pos.x)) = pos.z;
	}

	float FrameBuffer::getOnePosDepth(glm::vec2 pos) 
	{
		if (pos.x < 0 || pos.x >= m_width || pos.y < 0 || pos.y >= m_height)
			return 999;
		return *(m_depth.data() + int(pos.y * m_width + pos.x));
	}

	unsigned char* FrameBuffer::getBufferData()
	{
		return m_buffer.data();
	}
}

