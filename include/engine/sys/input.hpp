#pragma once

#include <GLFW/glfw3.h>

#include "engine/system.hpp"

namespace engine {

	namespace input_callback {
		void key_c(GLFWwindow *win, int key, int scancode, int action, int mods);
		void char_c(GLFWwindow *win, unsigned int key);
		void mouse_btn_c(GLFWwindow *win, int button, int action, int mods);
	}
	
	void sys_input_attach(GLFWwindow *win);

	class sys_input : public system {
	
	public:
		sys_input();
		~sys_input();

		void init();
		void shut_down();
		void update(float dt);
		
	};

}
