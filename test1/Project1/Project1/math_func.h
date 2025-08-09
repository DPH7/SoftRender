#pragma once
#include "glm/glm.hpp"
#include "vertex_output.h"
#include <vector>
#include <algorithm>

using namespace glm;

namespace SoftRender {
	namespace MathFunc {
		template<class T>
		T lerp(T& _v1, T& _v2, float _factor)
		{
			return _v1 + (_v2 - _v1) * _factor;
		}

		static VertexOutput Lerp(VertexOutput _data1, VertexOutput _data2, float _factor)
		{
			VertexOutput answer;
			answer.m_worldPos = lerp(_data1.m_worldPos, _data2.m_worldPos, _factor);
			answer.m_color= lerp(_data1.m_color, _data2.m_color, _factor);
			answer.m_normal = lerp(_data1.m_normal, _data2.m_normal, _factor);
			answer.m_textrue = lerp(_data1.m_textrue, _data2.m_textrue, _factor);
			answer.m_windowPos = lerp(_data1.m_windowPos, _data2.m_windowPos, _factor);
			answer.m_z = lerp(_data1.m_z, _data2.m_z, _factor);
			return answer;
		}

		//͸��ͶӰ ���� fov(����) aspect near far
		//M = [   1/aspect*tan(fov/2),       0      ,         0      ,       0
		//               0  ,         1/tan(fov/2)  ,         0      ,       0 
		//               0  ,                0      ,  - (f+n)/(f-n) ,  -2fn/(f-n)
		//               0  ,                0      ,         -1     ,       0     ]
		// ͶӰ֮�������ϵ���������ϵ��Z������Ļ���Ǹ�
		static mat4 GetPerspectiveMatrix(const float& fovy, const float& aspect, const float& n, const float& f)
		{
			glm::mat4 result = glm::mat4(0.0f);
			const float tanHalfFov = tan(fovy * 0.5f);
			result[0][0] = 1.0f / (aspect * tanHalfFov);
			result[1][1] = 1.0f / (tanHalfFov);
			result[2][2] = -(f + n) / (f - n);
			result[2][3] = -1.0f;
			result[3][2] = (-2.0f * n * f) / (f - n);

			return result;
		}

		//�۲����
		// V = R*T
		// T = [  1 , 0 , 0 , -eyex          R = [  Right , 0 
		//        0 , 1 , 0 , -eyey                   UP  , 0
		//        0 , 0 , 1 , -eyez               - Front , 0
		//        0 , 0 , 0 ,   1   ]                 0   , 1 ]
		//V =  [  Right  ,  - Right��eye
		//          UP   ,  - UP��eye
		//       -Front  ,   Front��eye
		//         0     ,       1        ]
		// ����ռ�һ��������ϵ��������ĻΪ+Z����������ӽǿ���ȥ�Ļ�+Z�ǳ�����Ļ���
		// Ϊ���ó��򱣳ֲ��䣬��Front����ȡ��
		static glm::mat4 GetViewMatrix(glm::vec3 pos, glm::vec3 front, glm::vec3 right, glm::vec3 up) {
			glm::mat4 result = glm::mat4(1.0f);
			result[0][0] = right.x;
			result[1][0] = right.y;
			result[2][0] = right.z;
			result[3][0] = -glm::dot(right, pos);
			result[0][1] = up.x;
			result[1][1] = up.y;
			result[2][1] = up.z;
			result[3][1] = -glm::dot(up, pos);
			result[0][2] = -front.x;
			result[1][2] = -front.y;
			result[2][2] = -front.z;
			result[3][2] = glm::dot(front, pos);
			return result;
		}


	}
}