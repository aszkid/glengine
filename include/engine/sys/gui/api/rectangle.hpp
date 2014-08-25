#pragma once

#include "drawable.hpp"

#include <array>

namespace engine { namespace gui { namespace api {

	class rectangle : public drawable {
		
		struct vert_t {
			glm::vec2 pos;
			glm::vec4 col;
		};
		
		
		void upload();
		void upload_init();
		
		std::array<vert_t, 4>* gen_vert_data();
		
	public:
		// shape data
		glm::vec2 m_size;
		glm::vec2 m_pos;
		glm::vec4 m_color;
		
		rectangle(glm::mat4 *viewprojmat, const glm::vec2 size, const glm::vec2 pos, const glm::vec4 color);
		~rectangle();
		
		void draw();
		
		// setters
		void set_position(const glm::vec2 pos);
		void set_color(const glm::vec4 color);
	
	};

}}}
