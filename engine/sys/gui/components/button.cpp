#include "engine/sys/gui/components/button.hpp"

using namespace engine::gui::component;

button::button(glm::vec2 pos, glm::vec2 size)
{
	m_prog.add_shader(GL_FRAGMENT_SHADER, "../../../rundir/shaders/2dsurf_frag.glsl");
	m_prog.add_shader(GL_VERTEX_SHADER, "../../../rundir/shaders/2dsurf_vert.glsl");
	m_prog.link();
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glGenBuffers(1, &vbo);
	
	GLfloat vertices[] = {
		-0.5f, -0.5f,
		-0.5f, +0.5f,
		+0.5f, -0.5f,
		+0.5f, +0.5f
	};
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	m_prog.set_attrib_ptr("position", 2, GL_FLOAT, GL_FALSE, 0, 0);
	
	m_uni_color = m_prog.get_uni_loc("surfColor");
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
button::~button()
{}

void button::draw()
{
	glBindVertexArray(vao);
	m_prog.use();
	glUniform4f(m_uni_color, 1.0f, 1.0f, 1.0f, 0.25f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}
