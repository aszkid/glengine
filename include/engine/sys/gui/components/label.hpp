#pragma once

#include <vector>
#include <string>

#include <freetype-gl.h>
#include <vertex-buffer.h>

#include "../base.hpp"
#include "engine/tools/shader.hpp"
#include "engine/sys/gui/helpers.hpp"

namespace engine { namespace gui {

	namespace component {
	
		class label : public base {
		private:
			tools::shader_program m_prog;
			vertex_buffer_t *m_buffer;
			texture_font_t *m_font;
			texture_atlas_t *m_atlas;
			GLuint m_uni_mat, m_uni_tex;
		public:
			glm::vec2 m_pos;
			int m_width;
			
			label(layout *par_layout, const wchar_t *text, int size, const glm::vec2 pos = glm::vec2(0), const glm::vec4 col = glm::vec4(.1, .1, .1, 1), const char* fontfile = "\0");
			~label();
			
			void update();
			void draw();
		};
	
	}

}}
