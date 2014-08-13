#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "engine/globals.hpp"

namespace engine {

	namespace gui {
		
		class layout;
		
		// base gui component
		class base {
		protected:
			glm::ivec2 *m_viewport;
			glm::mat4 *m_viewprojmat;
			GLuint m_uni_mat;
			
		public:
			base(glm::ivec2 *viewport, glm::mat4 *viewprojmat);
			virtual ~base();
			
			void set_viewport(glm::ivec2 *viewport);
			
			virtual void draw();
			
		};
		
	}


}
