#include "render_system.h"
#include "global_context.h"

namespace SoftRender {
	void RenderSystem::initialize(window_info info)
	{
		m_buffer.initialize(info);
	}

	void RenderSystem::pipeLine()
	{
		//�����һ֡
		m_buffer.clearBuffer(vec4(0.2f, 0.3f, 0.3f, 1.0f));

		drawModel();

		//����apiͼ����ʾ
		window_info info;
		glDrawPixels(info.width, info.height, GL_RGBA, GL_UNSIGNED_BYTE, m_buffer.getBufferData());
		glFlush();
	}
	void RenderSystem::tick(float time)
	{
		pipeLine();
	}

	void RenderSystem::addModel(Model _model)
	{
		m_model.push_back(_model);
	}

	Model* RenderSystem::getOneModel(int index)
	{
		return index <= m_model.size() ? &(m_model[index]) : nullptr;
	}

	mat4 RenderSystem::getViewPortMatrix(int x, int y, int width, int height)
	{
		glm::mat4 result = glm::mat4(1.0f);
		result[0][0] = width / 2.0f;
		result[3][0] = x + (width / 2.0f);
		result[1][1] = height / 2.0f;
		result[3][1] = y + (height / 2.0f);
		return result;
	}

	void RenderSystem::PerspectiveDivision(VertexOutput& v) {
		v.m_z = 1 / v.m_windowPos.w;
		v.m_windowPos /= v.m_windowPos.w;
		v.m_windowPos.w = 1.0f;
		// OpenGL的Z-Buffer是 [0,1]
		v.m_windowPos.z = (v.m_windowPos.z + 1.0) * 0.5;

		v.m_worldPos *= v.m_z;
		v.m_normal *= v.m_z;
		v.m_textrue *= v.m_z;
		v.m_color *= v.m_z;
	}

	void RenderSystem::rasterize(VertexOutput v1, VertexOutput v2, VertexOutput v3)
	{
		vector<VertexOutput> temp = { v1, v2, v3 };
		sort(temp.begin(), temp.end(), [](VertexOutput a, VertexOutput b) {
			return a.m_windowPos.y < b.m_windowPos.y;
			});

		if (temp[0].m_windowPos.y == temp[1].m_windowPos.y)
		{
			scanTriangle(temp[0], temp[1], temp[2]);
		}
		else if ((temp[1].m_windowPos.y == temp[2].m_windowPos.y))
		{
			scanTriangle(temp[1], temp[2], temp[0]);
		}
		else
		{
			float delta = (temp[1].m_windowPos.y - temp[0].m_windowPos.y) / (temp[2].m_windowPos.y - temp[0].m_windowPos.y);
			VertexOutput newElse = MathFunc::Lerp(temp[0], temp[2], delta);
			scanTriangle(temp[1], newElse, temp[0]);
			scanTriangle(temp[1], newElse, temp[2]);
		}
	}
	void RenderSystem::scanTriangle(VertexOutput v1, VertexOutput v2, VertexOutput v3)
	{
		VertexOutput left, right, elseOne;
		left = v1.m_windowPos.x >= v2.m_windowPos.x ? v2 : v1;
		right = v1.m_windowPos.x >= v2.m_windowPos.x ? v1 : v2;
		elseOne = v3;

		int offsetY = abs(elseOne.m_windowPos.y - left.m_windowPos.y);
		int elseY = v3.m_windowPos.y;
		bool ifUpTag = elseY > left.m_windowPos.y;
		for (int num = offsetY - 1; num >= 0; num--)
		{
			if (!offsetY)
			{
				break;
			}
			float delta = float(num) / offsetY;
			VertexOutput newLeft = MathFunc::Lerp(left, elseOne, delta);
			VertexOutput newRight = MathFunc::Lerp(right, elseOne, delta);

			newLeft.m_windowPos.x = int(newLeft.m_windowPos.x);
			newRight.m_windowPos.x = int(newRight.m_windowPos.x);
			if (ifUpTag) {
				newLeft.m_windowPos.y = newRight.m_windowPos.y = --elseY;
			}
			else {
				newLeft.m_windowPos.y = newRight.m_windowPos.y = ++elseY;
			}


			scanLine(newLeft, newRight);
		}

	}
	void RenderSystem::scanLine(VertexOutput v1, VertexOutput v2)
	{
		int offsetX = abs(v1.m_windowPos.x - v2.m_windowPos.x);
		for (int num = offsetX - 1; num >= 0; num--)
		{
			float delta = float(num) / offsetX;
			VertexOutput newPoint = MathFunc::Lerp(v1, v2, delta);
			newPoint.m_windowPos.x = v1.m_windowPos.x + num;
			newPoint.m_windowPos.y = v1.m_windowPos.y;

			float tempDepth = m_buffer.getOnePosDepth(vec2(newPoint.m_windowPos.x, newPoint.m_windowPos.y));
			if (newPoint.m_windowPos.z <= tempDepth)
			{
				// 还原一下
				newPoint.m_worldPos /= newPoint.m_z;
				newPoint.m_textrue /= newPoint.m_z;
				newPoint.m_normal /= newPoint.m_z;
				newPoint.m_color /= newPoint.m_z;

				m_buffer.drawOnePos(vec3(newPoint.m_windowPos.x, newPoint.m_windowPos.y, newPoint.m_windowPos.z), m_tempMtl->m_fragmentShader->shader(newPoint));
			}
		}
	}
	void RenderSystem::drawMesh(Mesh tempMesh, Object tempObject)
	{
		auto it = tempMesh;
		m_tempMtl = tempObject.m_material;

		for (int i = 0; i < it.m_ebo.size(); i += 3)
		{
			auto v1 = it.m_vbo[it.m_ebo[i]];
			auto v2 = it.m_vbo[it.m_ebo[i + 1]];
			auto v3 = it.m_vbo[it.m_ebo[i + 2]];

			auto o1 = m_tempMtl->m_vertexShader->shader(v1);
			auto o2 = m_tempMtl->m_vertexShader->shader(v2);
			auto o3 = m_tempMtl->m_vertexShader->shader(v3);


			//透视除法
			PerspectiveDivision(o1);
			PerspectiveDivision(o2);
			PerspectiveDivision(o3);

			/*
			o1.m_windowPos = vec4(0, 0.5, 0, 0);
			o2.m_windowPos = vec4(1, 1, 0, 0);
			o3.m_windowPos = vec4(0.8, 0.3, 0, 0);


			o1.m_color = vec4(0.33, 0.22, 0.33, 1);
			o2.m_color = vec4(0.76, 0.35, 0.33, 1);
			o3.m_color = vec4(0.91, 0.57, 0.33, 1);
			*/

			//�ӿ�ת��
			window_info info;
			auto viewPortMatrix = getViewPortMatrix(0, 0, info.width, info.height);
			o1.m_windowPos = viewPortMatrix * o1.m_windowPos;
			o2.m_windowPos = viewPortMatrix * o2.m_windowPos;
			o3.m_windowPos = viewPortMatrix * o3.m_windowPos;

			//��դ��
			rasterize(o1, o2, o3);
		}
	}

	void RenderSystem::drawModel()
	{
		for (auto temp : m_model) {
			m_tempModelMat = temp.getModelMat();
			for (auto temp2 : temp.m_objects) {
				if (temp2.m_mesh.m_ebo.empty()) {
					continue;
				}

				drawMesh(temp2.m_mesh, temp2);
			}
		}
	}
}
