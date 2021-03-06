#pragma once

#include "../base.hpp"
#include "engine/shader_manager.hpp"

#include "label.hpp"

#include <array>
#include <vector>

#include "glm/ext.hpp"

namespace engine { namespace gui {

	namespace component {
	
		struct vertex {
			vertex() {}
			vertex(glm::vec2 _vert, glm::vec4 _col) : vert(_vert), col(_col) {}
		
			glm::vec2 vert;
			glm::vec4 col;
		};
	
		enum class btn_state {
			NONE,
			HOVER,
			CLICK
		};
	
		class button : public base {
		private:
			tools::shader_program *m_prog;
			
			label *m_label;
			std::array<vertex, 4> m_vbodat;
			GLuint m_vao, m_vbo, m_ebo;
			
			btn_state m_state;
			
			void handle_click();
			void handle_event();
			bool mouse_in();
			
		public:
			glm::vec2 m_pos;
			glm::vec2 m_size;
			glm::vec4 m_col;
			int m_margin;
			
			button(layout *par_layout, const std::string text, glm::vec2 pos, int margin, glm::vec2 size = glm::vec2(-1,-1), glm::vec4 col = glm::vec4(0.1, 0.1, 0.1, 1));
			~button();
			
			void update();
			void draw();
			
			void upload();
			
			button* set_col(const glm::vec4 col);
			button* set_font(const std::string file);
			button* set_pos(const glm::vec2 pos);
			button* set_size(const glm::vec2 size);
		};
	
	}

}}
