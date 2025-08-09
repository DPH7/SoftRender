#pragma once
#include "globel.h"
#include "vertex.h"
#include "vertex_output.h"
#include "global_context.h"

using namespace glm;

namespace SoftRender
{
	class FragmentShaderBasic {
	public:
		FragmentShaderBasic() {
			initShader();
		}
		virtual void initShader()
		{

		}
		virtual vec4 shader(VertexOutput _input)
		{
			/*»ù´¡£ºÂþ·´Éä*/
			return vec4();
		}

	private:

	};
}