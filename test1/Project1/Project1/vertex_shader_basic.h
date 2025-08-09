#pragma once
#include "vertex.h"
#include "vertex_output.h"
#include "camera_system.h"
#include "render_system.h"
#include "global_context.h"
using namespace glm;

namespace SoftRender
{
	class VertexShaderBasic {
	public:
		VertexShaderBasic() {
			initShader();
		}
		virtual void initShader() {
		}
		virtual VertexOutput shader(Vertex _input)
		{
			return	VertexOutput();
		}
	};
}