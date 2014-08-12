#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace engine {

	namespace gui {
		
		// base gui component
		class base {
		public:
			base();
			virtual ~base();
			
			virtual void draw();
		};
		
	}


}
