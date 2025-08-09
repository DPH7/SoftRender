#include "window_system.h"
#include "global_context.h"

#include "input_system.h"
using namespace std;

namespace SoftRender {

	void SoftRender::WindowSystem::initialize(window_info info)
	{
        //初始化、版本以及模式设置
        glfwInit();
        
        //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
        //ios系统
        //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        m_window = glfwCreateWindow(info.width, info.height, info.title, NULL, NULL);
        if (m_window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
        }
        glfwMakeContextCurrent(m_window);

        //glad初始化
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
        }
	}

    GLFWwindow* WindowSystem::getCurWindow()
    {
        return m_window;
    }

	void WindowSystem::framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
        glViewport(0, 0, width, height);
	}

	void WindowSystem::processInput(GLFWwindow* window)
	{
        g_runtime_global_context.m_input_system->processInput(window);
	}

    bool WindowSystem::ifShouldClose()
    {
        return glfwWindowShouldClose(m_window);
    }

    void WindowSystem::setWindowTitle(const char* title)
    {
        glfwSetWindowTitle(m_window, title);
    }   

}
