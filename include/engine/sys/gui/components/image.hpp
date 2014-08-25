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
			GLuint m_vao, m_vbo, m_texid, m_ebo;
			
			GLuint m_uni_mat, m_uni_tex;
			
			std::string m_file;
			
			struct vert_t {
				vert_t() {}
				vert_t(glm::vec2 pos, glm::vec2 tcoord) : m_pos(pos), m_tcoord(tcoord) {}
				
				glm::vec2 m_pos;
				glm::vec2 m_tcoord;
				
				float ddd;
			};
			
			glm::vec2 m_texs;
			
			std::array<vert_t, 4> m_verts;
			
		public:
			glm::vec2 m_pos;
			glm::vec2 m_size;
			
			image(layout *par_layout, const std::string file, glm::vec2 pos = glm::vec2(0), glm::vec2 size = glm::vec2(128));
			~image();
			
			void handle_event();
			
			void update();
			void draw();
		};
	
	}

}}
