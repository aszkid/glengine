#pragma once

#include "drawable.hpp"

#include <array>

namespace engine { namespace gui { namespace api {

	class triangle : public drawable {
		
		struct vert_t {
			glm::vec2 pos;
			glm::vec4 col;
		};
		
		std::array<glm::vec2, 3> m_verts;
		glm::vec4 m_color;
		
		// gl data
		GLuint m_vao, m_vbo, m_ebo;
		
	public:
		triangle(const std::array<glm::vec2, 3> verts, const glm::vec4 color);
		~triangle();
		
		void draw();
	
	};

}}}
