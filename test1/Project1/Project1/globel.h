#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>

#include <memory>
#include <string>
namespace SoftRender {

}

using namespace std;
using namespace glm;
using namespace SoftRender;

enum MatType {
	ALBEDO,
	METALLIC,
	NORMAL,
	HEIGHT,
	OCCLUSION,
	ROUGHNESS
};
