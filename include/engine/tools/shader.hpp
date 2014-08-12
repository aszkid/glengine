#pragma once

#include <GL/glew.h>

#include <vector>

namespace engine {

	namespace tools {
	
		struct shader {		
			GLuint m_type;
			GLuint m_id;
		};
		
		class shader_program {
		private:
			GLuint m_program;
			std::vector<shader> m_shaders;
		public:
			
		};
	
	}

}
