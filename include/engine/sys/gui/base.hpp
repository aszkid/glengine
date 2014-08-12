#pragma once

#include <GL/glew.h>

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
