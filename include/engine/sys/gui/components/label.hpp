#pragma once

#include <vector>

#include <freetype-gl.h>
#include <vertex-buffer.h>

#include "../base.hpp"
#include "engine/tools/shader.hpp"
#include "engine/sys/gui/helpers.hpp"

namespace engine { namespace gui {

	namespace component {
	
		typedef struct {
			float x, y, z; // position
			float s, t; // texture
			float r, g, b, a; // color
		} vertex_t;
	
		class label : public base {
		private:
			tools::shader_program m_prog;
			glm::vec2 m_pos;
			vertex_buffer_t *m_buffer;
			texture_font_t *m_font;
			texture_atlas_t *m_atlas;
			GLuint m_uni_mat, m_uni_tex;
		public:
			label(layout *par_layout, glm::vec2 pos = glm::vec2(0));
			~label();
			
			void update();
			void draw();
		};
	
	}

}}
