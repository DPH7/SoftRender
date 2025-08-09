#pragma once
#include "fragment_shader_basic.h"
#include "render_system.h"

using namespace glm;

namespace SoftRender
{
	class FragmentShader : public FragmentShaderBasic {
	public:
		FragmentShader() {
			initShader();
		}

		~FragmentShader() = default;

		virtual void initShader()
		{

		}
		virtual vec4 shader(VertexOutput _input)
		{
			/*»ù´¡£ºÂþ·´Éä*/
			auto tempMatrial = g_runtime_global_context.m_render_system->getCurMatrial();
			auto cameraPos = g_runtime_global_context.m_camera_system->m_position;
			auto albedo = tempMatrial->sampleFromUV(MatType::ALBEDO, _input.m_textrue);
			auto worldNormal = normalize(_input.m_normal);
			auto worldViewDir = normalize(cameraPos - (_input.m_worldPos));


			return tempMatrial->sampleFromUV(MatType::ALBEDO, _input.m_textrue);
		}

	private:

	};
}