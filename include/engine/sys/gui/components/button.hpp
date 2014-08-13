#pragma once

#include "../base.hpp"
#include "engine/tools/shader.hpp"

namespace engine { namespace gui {

	namespace component {
	
		class button : public base {
		private:
			tools::shader_program m_prog;
			glm::vec2 m_pos;
			glm::vec2 m_size;
			GLuint vao, vbo;
			GLint m_uni_color;
		public:
			button(layout *par_layout, glm::vec2 pos = glm::vec2(0), glm::vec2 size = glm::vec2(75, 20));
			~button();
			
			void draw();
		};
	
	}

}}
