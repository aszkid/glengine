#include "engine/tools/shader.hpp"

using namespace engine::tools;

void shader_program::add_shader(const GLuint type, const std::string filename)
{
	std::ifstream in(filename, std::ios::in);
	if(!in.is_open()) {
		throw std::runtime_error(MKSTR("Shader (" << type << ":" << filename << ") failed to open!"));
	}
	
	std::string contents;
	in.seekg(0, std::ios::end);
	contents.resize(in.tellg());
	in.seekg(0, std::ios::beg);
	in.read(&contents[0], contents.size());
	const char* source = contents.c_str();
	
	shader s;
	s.m_id = glCreateShader(type);
	glShaderSource(s.m_id, 1, &source, NULL);
	
	glCompileShader(s.m_id);
	GLint status;
	glGetShaderiv(s.m_id, GL_COMPILE_STATUS, &status);
	char buffer[512];
	glGetShaderInfoLog(s.m_id, 512, NULL, buffer);
	LOG("DEBUG", buffer);
	if(status != GL_TRUE) {
		throw std::runtime_error(MKSTR("Failed to compile '" << filename << "'!"));
	}
}
void shader_program::link()
{
	m_id = glCreateProgram();
	for(shader s : m_shaders) {
		glAttachShader(m_id, s.m_id);
	}
	glLinkProgram(m_id);
}

void shader_program::use()
{
	glUseProgram(m_id);
}

GLint shader_program::pos_attrib(const std::string pos)
{
	return glGetAttribLocation(m_id, pos.c_str());
}

