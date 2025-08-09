#pragma once
#include "window_system.h"
#include "glm/glm.hpp"
#include <vector>

namespace SoftRender {
	class FrameBuffer {
	public:
		void initialize(window_info windowInfo);
		void clearBuffer(glm::vec4 color);
		void drawOnePos(glm::vec3 pos, glm::vec4 color);
		unsigned char* getBufferData();
		float getOnePosDepth(glm::vec2 pos);
	private:
		int m_width;
		int m_height;
		std::vector<unsigned char> m_buffer;
		std::vector<float> m_depth;
	};
}
