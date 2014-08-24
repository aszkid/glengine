#pragma once

#include <vector>

#include "../base.hpp"
#include "engine/tools/shader.hpp"
#include "engine/sys/gui/helpers.hpp"

namespace engine { namespace gui {

	namespace component {
	
		class image : public base {
		private:
			tools::shader_program m_prog;
			GLuint m_vao, m_vbo;
			
			std::string m_file;
			
			struct vert_t {
				vert_t(glm::vec2 pos, glm::vec2 size) : m_pos(pos), m_size(size) {}
				
				glm::vec2 m_pos;
				glm::vec2 m_size;
				
				float ddd;
			};
			
		public:
			glm::vec2 m_pos;
			glm::vec2 m_size;
			
			image(layout *par_layout, const std::string file, glm::vec2 pos = glm::vec2(0), glm::vec2 size = glm::vec2(100));
			~image();
			
			void handle_event();
			
			void update();
			void draw();
		};
	
	}

}}
