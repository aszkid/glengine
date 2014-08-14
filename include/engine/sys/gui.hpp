#pragma once

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <vector>
#include <memory>

#include "engine/system.hpp"
#include "gui/layout.hpp"

#include "gui/components/button.hpp"
#include "gui/components/window.hpp"

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
		glm::mat4 m_viewprojmat;
		glm::vec2 m_cursorpos;
		
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
		
		FT_Face new_face(const char *filename);
		
		layout_handle new_layout();
	};

}
