#pragma once

#include "../base.hpp"
#include "engine/tools/shader.hpp"

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
	
		class button : public base {
		private:
			tools::shader_program m_prog;
			glm::vec2 m_pos;
			glm::vec2 m_size;
			
			label *m_label;
			
			GLuint vao, vbo;
		public:
			button(layout *par_layout, const std::string text, glm::vec2 pos, int margin, glm::vec2 size = glm::vec2(-1,-1), glm::vec4 col = glm::vec4(0.1, 0.1, 0.1, 1));
			~button();
			
			void update();
			void draw();
		};
	
	}

}}
