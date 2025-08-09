#pragma once
#include "mesh.h"

namespace SoftRender
{
	class Material;
	class Object {
	public:
		Object() = default;
		~Object() = default;
		Object(const Mesh& m, Material* mat) {
			m_mesh = m;
			m_material = mat;
		}

		void setMat(Material* mat) {
			m_material = mat;
		}
	public:
		Mesh m_mesh;
		Material* m_material;
	};
}
