#pragma once

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <vector>
#include <memory>

#include "engine/system.hpp"
#include "gui/layout.hpp"

#include "gui/components/button.hpp"

namespace engine {

	class sys_gui : public system {
	
	private:
		typedef std::vector<std::unique_ptr<gui::layout>> layout_list;
		typedef gui::layout* layout_handle;
		
		layout_list m_layouts;
		layout_handle m_active_layout;
		
		FT_Library m_ft;
		
		GLFWwindow *m_win;
		glm::ivec2 m_viewport;
		
	public:
		sys_gui(GLFWwindow *win);
		~sys_gui();

		void init();
		void shut_down();
		void update(float dt);
		void handle_event(event_t event);
		void draw();
		
		FT_Face new_face(const char *filename);
		
		layout_handle new_layout();
	};

}
