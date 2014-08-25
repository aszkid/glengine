#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

namespace engine { namespace gui { namespace api {

	class drawable {
	protected:
		GLuint m_vao, m_vbo, m_ebo;
	public:
		drawable() {};
		virtual ~drawable() {};
		
		virtual void draw() = 0;
	
	};

}}}
