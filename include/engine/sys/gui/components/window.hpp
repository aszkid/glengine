#pragma once

#include <vector>

#include "../base.hpp"
#include "engine/tools/shader.hpp"
#include "engine/sys/gui/helpers.hpp"

namespace engine { namespace gui {

	namespace component {
	
		class window : public base {
		private:
			tools::shader_program m_prog;
			GLuint vao, vbo;
			
			GLuint m_ele_buffer;
			
			color m_bg_color;
			float m_margin;
			float m_top_margin;
			std::vector<uint> m_indices;
			std::array<vbo_data, 16> m_vbodat;
			glm::vec2 m_pos;
			glm::vec2 m_size;
		public:
			window(layout *par_layout, glm::vec2 pos = glm::vec2(0), glm::vec2 size = glm::vec2(75, 20));
			~window();
			
			void handle_event();
			
			void update();
			void draw();
		};
	
	}

}}
