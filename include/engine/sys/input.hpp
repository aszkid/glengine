#pragma once

#include "engine/globals.hpp"
#include "engine/system.hpp"
#include "engine/event_manager.hpp"

namespace engine {

	namespace input_callback {
		void key_c(GLFWwindow *win, int key, int scancode, int action, int mods);
		void char_c(GLFWwindow *win, unsigned int key);
		void mouse_btn_c(GLFWwindow *win, int button, int action, int mods);
		void win_size_c(GLFWwindow *win, int x, int y);
		void cursor_pos_c(GLFWwindow *win, double x, double y);
		void win_close_c(GLFWwindow *win);
	}
	
	void sys_input_attach(GLFWwindow *win);

	class sys_input : public system {
	
	public:
		sys_input();
		~sys_input();

		void init();
		void shut_down();
		void update(float dt);
		void handle_event(event_t *event);
		
	};

}
