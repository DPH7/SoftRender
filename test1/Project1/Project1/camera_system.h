#pragma once
#include "math_func.h"
#include "gameObject.h"
using namespace glm;

namespace SoftRender {
	class CameraSystem : public GameObject{
	public:
		float m_fov;
		float m_aspect;

		float m_near;
		float m_far;


		//位置 垂直反转 看的目标点 Fov 宽 高
		CameraSystem(
			vec3 position = vec3(0.0f, 0.0f, 3.0f),
			vec3 up = vec3(0.0f, 1.0f, 0.0f),
			vec3 lookat = vec3(0.0f, 0.0f, 0.0f),
			float fov = 60.0f,
			int w = 800,
			int h = 600,
			float n = 0.3f,
			float f = 100
		) : GameObject(vec4(position, 1))
		{
			
			m_near = n;
			m_far = f;
			m_fov = radians(fov);
			m_aspect = ((float)w / h);
		}
		mat4 ViewMatrix()
		{
			auto angleMat = getAngelMat();
			return MathFunc::GetViewMatrix(m_position, -angleMat[2], angleMat[0], angleMat[1]);
		}

		mat4 PerspectiveMatrix()
		{
			return MathFunc::GetPerspectiveMatrix(m_fov, m_aspect, m_near, m_far);
		}
		void UpdateFov(float fov = 60.0f) {
			m_fov = radians(fov);
		}
		void UpdateAspect(int w, int h) {
			m_aspect = (float)w / h;
		}
	};
}
