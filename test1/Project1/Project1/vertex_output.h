#pragma once
#include "glm/glm.hpp"

using namespace glm;

namespace SoftRender
{
	class VertexOutput {
	public:
		vec4 m_worldPos;
		vec4 m_windowPos;
		vec4 m_color;
		vec2 m_textrue;
		vec3 m_normal;
		float m_z = 0;

		VertexOutput() = default;
		~VertexOutput() = default;

		VertexOutput(const VertexOutput& _data)
		{
			m_worldPos = _data.m_worldPos;
			m_windowPos = _data.m_windowPos;
			m_color = _data.m_color;
			m_textrue = _data.m_textrue;
			m_normal = _data.m_normal;
			m_z = _data.m_z;
		}
	};
}