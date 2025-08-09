#pragma once
#include "vertex.h"
#include "globel.h"

namespace SoftRender
{
	class Mesh {
	public:
		Mesh() = default;
		~Mesh() = default;

		void addTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3);

		std::vector<Vertex> m_vbo;
		std::vector<unsigned int> m_ebo;
	};
}