#pragma once

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <memory>

#include "engine/system.hpp"
#include "gui/layout.hpp"
#include "gui/helpers.hpp"

#include "gui/components/button.hpp"
#include "gui/components/window.hpp"
#include "gui/components/label.hpp"

namespace engine {

	class sys_gui : public system {
	
	private:
		typedef std::vector<std::unique_ptr<gui::layout>> layout_list;
		typedef gui::layout* layout_handle;
		
		layout_list m_layouts;
		
		GLFWwindow *m_win;
		glm::ivec2 m_viewport;
		glm::mat4 m_viewprojmat;
		
		gui::mouse_state m_mouse;
		
		void update_view();
		
	public:
		sys_gui(GLFWwindow *win);
		~sys_gui();

		void init();
		void shut_down();
		void update(float dt);
		void handle_event(event_t *event);
		void draw();
		
		glm::ivec2* get_viewport();
		
		layout_handle new_layout();
	};

}
