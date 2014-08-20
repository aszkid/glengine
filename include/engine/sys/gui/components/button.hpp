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
			vertex(glm::vec2 _vert) : vert(_vert) {}
		
			glm::vec2 vert;
		};
	
		class button : public base {
		private:
			tools::shader_program m_prog;
			glm::vec2 m_pos;
			glm::vec2 m_size;
			
			label *m_label;
			
			GLuint vao, vbo;
		public:
			button(layout *par_layout, glm::vec2 pos = glm::vec2(500, 500), glm::vec2 size = glm::vec2(75, 20));
			~button();
			
			void update();
			void draw();
		};
	
	}

}}
