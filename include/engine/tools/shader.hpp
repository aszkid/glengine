#pragma once

#include <GL/glew.h>

#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>

#include "../globals.hpp"

namespace engine {

	namespace tools {
	
		struct shader {		
			GLuint m_type;
			GLuint m_id;
		};
		
		struct shader_program {
			GLuint m_id;
			std::vector<shader> m_shaders;
			
			void add_shader(const GLuint type, const std::string filename);
			void link();
			void use();
			
			GLint get_uni_loc(const char *name);
			
			void set_attrib_ptr(const char *attrib_name, GLint size, 
				GLenum type, GLboolean norm, GLsizei stride, const GLvoid *ptr);
		};
	
	}

}
