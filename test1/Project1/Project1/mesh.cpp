#include "mesh.h"

void Mesh::addTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3)
{
	int curSize = m_vbo.size();
	m_vbo.push_back(v1);
	m_vbo.push_back(v2);
	m_vbo.push_back(v3);

	m_ebo.push_back(curSize);
	m_ebo.push_back(curSize + 1);
	m_ebo.push_back(curSize + 1);
}
