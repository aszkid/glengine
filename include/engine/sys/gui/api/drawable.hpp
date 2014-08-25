#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "engine/profiler.hpp"
#include "engine/shader_manager.hpp"

namespace engine { namespace gui { namespace api {

	class drawable {
	protected:
		// gl data
		GLuint m_vao, m_vbo, m_ebo;
		
		// shader
		tools::shader_program *m_prog;
		
		// uniform data
		glm::mat4 *m_viewprojmat;
		GLuint m_uni_mat;
	public:
		drawable(glm::mat4 *viewprojmat) : m_viewprojmat(viewprojmat) {};
		virtual ~drawable() {};
		
		virtual void draw() = 0;
	
	};

}}}
