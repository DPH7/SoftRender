#pragma once
#include "global_context.h"
#include "camera_system.h"
#include "render_system.h"

namespace SoftRender {
	class InputSystem {
	public :
		int m_action_model = 0;
	public:
		void processInput(GLFWwindow* window) {

			if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
				m_action_model = 0;
			}
			else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
				m_action_model = 1;
			}

			/*移动的物体*/
			GameObject* actionGameObject = nullptr;
			if (m_action_model >= 1) {
				actionGameObject = g_runtime_global_context.m_render_system->getOneModel(m_action_model - 1);
			}
			else {
				actionGameObject = g_runtime_global_context.m_camera_system.get();
			}

			/*关闭*/
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
				glfwSetWindowShouldClose(window, true);
			}

			/*转动*/
			if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
				actionGameObject->rotateAngle(vec3(-5, 0, 0));
			}
			if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
				actionGameObject->rotateAngle(vec3(0, 5, 0));
			}
			if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
				actionGameObject->rotateAngle(vec3(0, -5, 0));
			}
			if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
				actionGameObject->rotateAngle(vec3(5, 0, 0));
			}

			/*方向*/
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
				actionGameObject->moveDistance(vec3(0, 0.1, 0));
			}
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
				actionGameObject->moveDistance(vec3(0, -0.1, 0));
			}
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
				actionGameObject->moveDistance(vec3(-0.1, 0, 0));
			}
			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
				actionGameObject->moveDistance(vec3(0.1, 0, 0));
			}
		}
	};
}
