#pragma once
#include "math_func.h"
#include "globel.h"

namespace SoftRender {
	class WindowSystem;
	class InputSystem;
	class RenderSystem;
	class CameraSystem;

	class GlobalContext {
	public:
		void startSystem();
		void shutDownSystem();

	public:
		shared_ptr<WindowSystem> m_window_system;
		shared_ptr<InputSystem> m_input_system;
		shared_ptr<RenderSystem> m_render_system;
		shared_ptr<CameraSystem> m_camera_system;
	};

	extern GlobalContext g_runtime_global_context;
}