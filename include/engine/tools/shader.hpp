#pragma once

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
			shader_program();
			~shader_program();
		
			GLuint m_id;
			std::vector<shader> m_shaders;
			
			shader_program* add_shader(const GLuint type, const std::string filename);
			void link();
			void use();
			
			GLint get_attrib_loc(const char *name);
			GLint get_uni_loc(const char *name);
			
			void set_attrib_ptr(const char *attrib_name, const GLint size, 
				const GLenum type, const GLboolean norm, const GLsizei stride, const GLvoid *ptr);
		};
	
	}

}
