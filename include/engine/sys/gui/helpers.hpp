#pragma once

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>

#include <array>

namespace engine {

	namespace gui {
	
		struct color {
			float r, g, b, a;
			
			color(float _r = 0, float _g = 0, float _b = 0, float _a = 0) : r(_r), g(_g), b(_b), a(_a) {}
			color normalize() { return color(r / 255.f, g / 255.f, b / 255.f, a / 255.f); }
		};
		
		struct vbo_data {
			glm::vec2 vert;
			glm::vec4 color;
		};
	
	}

}
