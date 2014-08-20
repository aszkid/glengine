#pragma once

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>

// font rendering
#include <freetype-gl.h>
#include <vertex-buffer.h>

#include <array>

#include "engine/globals.hpp"

namespace engine {

	namespace gui {
	
		struct color {
			float r, g, b, a;
			
			color(float _r = 0, float _g = 0, float _b = 0, float _a = 0) : r(_r), g(_g), b(_b), a(_a) {}
			color normalize() { return color(r / 255.f, g / 255.f, b / 255.f, a / 255.f); }
		};
		
		struct vbo_data {
			glm::vec2 vert;
			int type;
		};
		
		struct mouse_state {
			mouse_state() : m_rclick(false), m_lclick(false) {}
		
			bool m_rclick;
			bool m_lclick;
			
			glm::vec2 m_pos;
		};
		
		typedef struct {
			float x, y, z; // position
			float s, t; // texture
			float r, g, b, a; // color
		} glyph_vertex_t;
		
		int add_text(vertex_buffer_t * buffer, texture_font_t * font, const wchar_t * text, vec4 * color, vec2 * pen);
	
	}

}
