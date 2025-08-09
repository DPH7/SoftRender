#pragma once
#include "vertex_shader_basic.h"
using namespace glm;

namespace SoftRender
{
	class VertexShader: public VertexShaderBasic {
	public:
		VertexShader() {
			initShader();
		}
		void initShader() {
		}
		VertexOutput shader(Vertex _input)
		{
			VertexOutput ans;
			ans.m_worldPos = g_runtime_global_context.m_render_system->getCurModelMat() * _input.m_pos;
			ans.m_windowPos = g_runtime_global_context.m_camera_system->PerspectiveMatrix() * g_runtime_global_context.m_camera_system->ViewMatrix() * ans.m_worldPos;
			ans.m_textrue = _input.m_textrue;

			//可以自定义一些效果

			return ans;
		}
	};
}