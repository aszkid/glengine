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
			GLuint m_uni_mat;
			layout *m_layout;
			
		public:
			base(layout *par_layout);
			virtual ~base();
			
			virtual void draw();
			
		};
		
	}


}
