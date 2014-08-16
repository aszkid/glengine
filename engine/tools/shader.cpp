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
	s.m_type = type;
	s.m_id = glCreateShader(type);
	glShaderSource(s.m_id, 1, &source, NULL);
	
	glCompileShader(s.m_id);
	GLint status;
	glGetShaderiv(s.m_id, GL_COMPILE_STATUS, &status);
	char buffer[512];
	glGetShaderInfoLog(s.m_id, 512, NULL, buffer);
	std::string rep(buffer);
	rep.pop_back();
	rep.pop_back();
	LOG("t_shader", log::INFO) << rep;
	if(status != GL_TRUE) {
		throw std::runtime_error(MKSTR("Failed to compile '" << filename << "'!"));
	}
	
	m_shaders.push_back(s);
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

GLint shader_program::get_uni_loc(const char *name)
{
	return glGetUniformLocation(m_id, name);
}
void shader_program::set_attrib_ptr(const char *attrib_name, GLint size, 
	GLenum type, GLboolean norm, GLsizei stride, const GLvoid *ptr)
{
	GLint attrib = glGetAttribLocation(m_id, attrib_name);
	glEnableVertexAttribArray(attrib);
	glVertexAttribPointer(attrib, size, type, norm, stride, ptr);
}

