#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "engine/globals.hpp"

namespace engine {

	namespace gui {
		
		// base gui component
		class base {
		protected:
			glm::ivec2 *m_viewport;
		public:
			base();
			virtual ~base();
			
			void set_viewport(glm::ivec2 *viewport);
			
			virtual void draw();
			
		};
		
	}


}
