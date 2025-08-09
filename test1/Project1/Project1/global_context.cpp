#pragma once
#include "global_context.h"
#include "window_system.h"
#include "input_system.h"
#include "render_system.h"
#include "camera_system.h"

namespace SoftRender {

	GlobalContext g_runtime_global_context;

	void GlobalContext::startSystem()
	{
		window_info windowInfo;
		m_window_system = make_shared<WindowSystem>();
		m_window_system->initialize(windowInfo);

		m_input_system = make_shared<InputSystem>();
		
		m_render_system = make_shared<RenderSystem>();
		m_render_system->initialize(windowInfo);

		m_camera_system = make_shared<CameraSystem>();
	}

	void GlobalContext::shutDownSystem()
	{
	}

}