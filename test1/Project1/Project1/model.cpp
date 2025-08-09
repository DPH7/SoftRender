#include "model.h"

Model::Model(std::string path)
{
	loadModelPath(path);
}

void Model::loadModelPath(string path)
{
	std::ifstream in(path);
	if (!in) {
		std::cout << "Open Obj File Error !" << std::endl;
		return;
	}

	std::vector<glm::vec3> vertexs;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> textrues;

	std::string line;

	int currentObjectNums = -1;
	bool flag = false;
	while (!in.eof()) {
		std::getline(in, line);
		if (!line.compare(0, 2, "v "))
		{
			if (!flag) {
				currentObjectNums++;
				Object o;
				m_objects.push_back(o);
				flag = true;
			}
			line = line.substr(2);
			std::istringstream iss(line);
			glm::vec3 v;
			iss >> v.x;
			iss >> v.y;
			iss >> v.z;
			vertexs.push_back(v);
			continue;
		}
		if (!line.compare(0, 3, "vn "))
		{
			line = line.substr(3);
			std::istringstream iss(line);
			glm::vec3 vn;
			iss >> vn.x;
			iss >> vn.y;
			iss >> vn.z;
			normals.push_back(vn);
			continue;
		}
		if (!line.compare(0, 3, "vt "))
		{
			line = line.substr(3);
			std::istringstream iss(line);
			glm::vec3 vt;
			iss >> vt.x;
			iss >> vt.y;
			vt.y = 1 - vt.y;
			//二维纹理 z=0
			iss >> vt.z;
			textrues.push_back(glm::vec2(vt.x, vt.y));
			continue;
		}
		if (!line.compare(0, 2, "f "))
		{
			if (flag)
				flag = false;
			line = line.substr(2);
			std::istringstream iss(line);
			char bar;
			int vIndex, vtIndex, vnIndex;
			// 1/1/1
			int offset = m_objects[currentObjectNums].m_mesh.m_vbo.size();
			for (int i = 0; i < 3; i++) {
				iss >> vIndex >> bar >> vtIndex >> bar >> vnIndex;
				Vertex vertex(vertexs[vIndex - 1], glm::vec4(1, 1, 1, 1), textrues[vtIndex - 1], normals[vnIndex - 1]);
				m_objects[currentObjectNums].m_mesh.m_vbo.push_back(vertex);
				m_objects[currentObjectNums].m_mesh.m_ebo.push_back(offset + i);
			}
			//计算切线
			glm::vec3 pos1 = m_objects[currentObjectNums].m_mesh.m_vbo[offset].m_pos;
			glm::vec3 pos2 = m_objects[currentObjectNums].m_mesh.m_vbo[offset + 1].m_pos;
			glm::vec3 pos3 = m_objects[currentObjectNums].m_mesh.m_vbo[offset + 2].m_pos;
			glm::vec2 uv1 = m_objects[currentObjectNums].m_mesh.m_vbo[offset].m_textrue;
			glm::vec2 uv2 = m_objects[currentObjectNums].m_mesh.m_vbo[offset + 1].m_textrue;
			glm::vec2 uv3 = m_objects[currentObjectNums].m_mesh.m_vbo[offset + 2].m_textrue;
			glm::vec3 edge1 = pos2 - pos1;
			glm::vec3 edge2 = pos3 - pos1;
			glm::vec2 deltaUV1 = uv2 - uv1;
			glm::vec2 deltaUV2 = uv3 - uv1;

			float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

			glm::vec3 m_tangent;
			m_tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
			m_tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
			m_tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
			m_tangent = glm::normalize(m_tangent);
			m_objects[currentObjectNums].m_mesh.m_vbo[offset].m_tangent = m_tangent;
			m_objects[currentObjectNums].m_mesh.m_vbo[offset + 1].m_tangent = m_tangent;
			m_objects[currentObjectNums].m_mesh.m_vbo[offset + 2].m_tangent = m_tangent;

			if (iss >> vIndex) {
				iss >> bar >> vtIndex >> bar >> vnIndex;
				Vertex vertex(vertexs[vIndex - 1], glm::vec4(1, 1, 1, 1), textrues[vtIndex - 1], normals[vnIndex - 1]);
				m_objects[currentObjectNums].m_mesh.m_vbo.push_back(vertex);
				m_objects[currentObjectNums].m_mesh.m_ebo.push_back(offset);
				m_objects[currentObjectNums].m_mesh.m_ebo.push_back(offset + 2);
				m_objects[currentObjectNums].m_mesh.m_ebo.push_back(offset + 3);
				pos1 = m_objects[currentObjectNums].m_mesh.m_vbo[offset].m_pos;
				pos2 = m_objects[currentObjectNums].m_mesh.m_vbo[offset + 2].m_pos;
				pos3 = m_objects[currentObjectNums].m_mesh.m_vbo[offset + 3].m_pos;
				uv1 = m_objects[currentObjectNums].m_mesh.m_vbo[offset].m_textrue;
				uv2 = m_objects[currentObjectNums].m_mesh.m_vbo[offset + 2].m_textrue;
				uv3 = m_objects[currentObjectNums].m_mesh.m_vbo[offset + 3].m_textrue;
				edge1 = pos2 - pos1;
				edge2 = pos3 - pos1;
				deltaUV1 = uv2 - uv1;
				deltaUV2 = uv3 - uv1;

				f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

				m_tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
				m_tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
				m_tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
				m_tangent = glm::normalize(m_tangent);
				m_objects[currentObjectNums].m_mesh.m_vbo[offset].m_tangent = m_tangent;
				m_objects[currentObjectNums].m_mesh.m_vbo[offset + 2].m_tangent = m_tangent;
				m_objects[currentObjectNums].m_mesh.m_vbo[offset + 3].m_tangent = m_tangent;
			}
			continue;
		}


	}
	in.close();
}
