#pragma once

#include <vector>
#include <string>

#include <freetype-gl.h>
#include <vertex-buffer.h>

#include "../base.hpp"
#include "engine/shader_manager.hpp"
#include "engine/sys/gui/helpers.hpp"

namespace engine { namespace gui {

	namespace component {
	
		class label : public base {
		private:
			tools::shader_program *m_prog;
			vertex_buffer_t *m_buffer;
			texture_font_t *m_font;
			texture_atlas_t *m_atlas;
			GLuint m_uni_mat, m_uni_tex;
			std::string m_fontfile;
		public:
			glm::vec2 m_bbox;
			glm::vec2 m_pos;
			glm::vec4 m_col;
			std::string m_str;
			int m_size;
			
			label* set_pos(const glm::vec2 pos);
			label* set_font(const std::string file);
			label* set_col(const glm::vec4 col);
			
			label(layout *par_layout, const std::string text, int size = 20, const glm::vec2 pos = glm::vec2(0), const glm::vec4 col = glm::vec4(.1, .1, .1, 1), const char* fontfile = "\0");
			~label();
			
			void handle_event();
			
			void upload(bool gen_glyphs = false);
			void update();
			void draw();
		};
	
	}

}}
