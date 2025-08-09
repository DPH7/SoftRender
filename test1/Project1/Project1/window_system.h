#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>
namespace SoftRender {
    struct window_info {
        int         width{800};
        int         height{600};
        const char* title{ "SoftRender" };
    };

    class WindowSystem {
    public:
        void initialize(window_info info);

        GLFWwindow* getCurWindow();

        void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        void processInput(GLFWwindow* window);

        bool ifShouldClose();

        void setWindowTitle(const char* title);
    private:
        GLFWwindow* m_window;     //´°¿Ú
    };
}
