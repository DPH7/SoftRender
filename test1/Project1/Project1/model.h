#pragma once
#include "object.h"
#include "gameObject.h"

namespace SoftRender
{
	class Model : public GameObject{
	public:
		Model() = default;
		~Model() = default;
		Model(std::string path);

		void loadModelPath(string path);

	public:
		std::vector<Object> m_objects;
	};
}