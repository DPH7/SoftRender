#pragma once
#include "glm/glm.hpp"
using namespace glm;

namespace SoftRender
{
	class Vertex {
	public:
		Vertex() = default;
		~Vertex() = default;

		Vertex(vec3 _pos = vec3(0, 0, 0), vec4 _color = vec4(0, 0, 0, 0),
			vec2 _texture = vec2(0, 0), vec3 _normal = vec3(0, 0, 0)) {
			m_pos = vec4(_pos, 1);
			m_color = _color;
			m_textrue = _texture;
			m_normal = _normal;
		}
		vec4 m_pos;
		vec4 m_color;
		vec2 m_textrue;
		vec3 m_normal;
		/*«–œÚ¡ø*/
		vec3 m_tangent;
	};
}