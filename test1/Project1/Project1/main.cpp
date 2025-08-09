#include "global_context.h"
#include <atomic>
#include <chrono>
#include <string>
#include "model.h"
#include "vertex_shader.h"
#include "fragment_shader.h"
#include "material.h"

#include "window_system.h"
#include "input_system.h"
#include "render_system.h"
#include "camera_system.h"

std::chrono::steady_clock::time_point m_last_tick_time_point{ std::chrono::steady_clock::now() };
int m_fps = 0;
int m_tick_num = 0;
float m_average_time = 0;
const float m_fps_alpha = 1 / 100.f;

float computeDeltaTime() {
    float ans;
    {
        using namespace std::chrono;
        steady_clock::time_point curTime = steady_clock::now();
        duration<float> time = duration_cast<duration<float>>(curTime - m_last_tick_time_point);
        ans = time.count();
        m_last_tick_time_point = curTime;
    }
    return ans;
}

void computeFps(float time) {
    m_tick_num++;

    if (m_tick_num == 1)
    {
        m_average_time = time;
    }
    else
    {
        m_average_time = m_average_time * (1 - m_fps_alpha) + time * m_fps_alpha;
    }

    m_fps = static_cast<int>(1.f / m_average_time);
}

int main()
{
    g_runtime_global_context.startSystem();    

    shared_ptr<WindowSystem> window = g_runtime_global_context.m_window_system;

    //������Ⱦ����
    Material wBoxMat;
    wBoxMat.setAlbedoUV("box\\Wooden_box_01_BaseColor.png");

    VertexShader vShader;
    FragmentShader fShader;
    wBoxMat.setVertexShader(&vShader);
    wBoxMat.setFragmentShader(&fShader);

    auto curModel = Model("box\\Wooden_stuff.obj");
    curModel.m_objects[0].setMat(&wBoxMat);

    g_runtime_global_context.m_render_system->addModel(curModel);

    while (!window->ifShouldClose())
    {
        auto glfwWindow = window->getCurWindow();
        window->processInput(glfwWindow);

        auto deltaTime = computeDeltaTime();

        computeFps(deltaTime);

        g_runtime_global_context.m_render_system->tick(deltaTime);

        window->setWindowTitle(("FPS:" + std::to_string(m_fps)).c_str());

        glfwSwapBuffers(glfwWindow);
        glfwPollEvents();
    }

    g_runtime_global_context.shutDownSystem();
    return 0;
}