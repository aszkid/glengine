#include "engine/sys/gui/components/window.hpp"

using namespace engine::gui::component;

window::window(glm::ivec2 *viewport, glm::mat4 *viewprojmat, glm::vec2 pos, glm::vec2 size)
	: engine::gui::base(viewport, viewprojmat)
{
	m_prog.add_shader(GL_FRAGMENT_SHADER, "../../../rundir/shaders/2dsurf_frag.glsl");
	m_prog.add_shader(GL_VERTEX_SHADER, "../../../rundir/shaders/2dsurf_vert.glsl");
	m_prog.link();
	
	// -----
	
	m_margin = 7.f;
	m_top_margin = m_margin * 3.25f;
	
	m_pos.x = 50.f;
	m_pos.y = 50.f;
	
	m_size.x = 640.f - m_margin*2;
	m_size.y = 360.f - m_margin - m_top_margin;
	
	m_indices = {
		0, 1, 2,
		2, 1, 3,
		3, 1, 4,
		3, 4, 5,
		5, 4, 6,
		5, 6, 7,
		9, 5, 7,
		9, 7, 8,
		11, 9, 8,
		11, 8, 10,
		12, 9, 11,
		12, 13, 9,
		14, 13, 12,
		14, 15, 13,
		15, 2, 3,
		15, 3, 13,
		13, 3, 5,
		13, 5, 9
	};	
	std::vector<GLfloat> vertices = {
		/*0*/  0.f, 0.f,
		/*1*/  0.f, m_top_margin,
		/*2*/  m_margin, 0.f,
		/*3*/  m_margin, m_top_margin,
		/*4*/  0.f, m_top_margin + m_size.y,
		/*5*/  m_margin, m_top_margin + m_size.y,
		/*6*/  0.f, m_margin + m_top_margin + m_size.y,
		/*7*/  m_margin, m_margin + m_top_margin + m_size.y,
		/*8*/  m_margin + m_size.x, m_margin + m_top_margin + m_size.y,
		/*9*/  m_margin + m_size.x, m_top_margin + m_size.y,
		/*10*/ m_margin*2 + m_size.x, m_margin + m_top_margin + m_size.y,
		/*11*/ m_margin*2 + m_size.x, m_top_margin + m_size.y,
		/*12*/ m_margin*2 + m_size.x, m_top_margin,
		/*13*/ m_margin + m_size.x, m_top_margin,
		/*14*/ m_margin*2 + m_size.x, 0.f,
		/*15*/ m_margin + m_size.x, 0.f
	};
	
	/*std::vector<GLfloat> vertices = {
		0.f, 0.f,
		0.f, 20.f,
		20.f, 0.f,
		20.f, 20.f
	};*/
	
	for(size_t i = 0; i < vertices.size(); i += 2) {
		vertices[i]   += m_pos.x;
		vertices[i+1] += m_pos.y;
	}
	
	// ----
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	// fill data
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
	// fill indices
	glGenBuffers(1, &m_ele_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ele_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

	// ----
	
	m_prog.set_attrib_ptr("position", 2, GL_FLOAT, GL_FALSE, 0, 0);
	
	m_uni_color = m_prog.get_uni_loc("surfColor");
	m_uni_mat = m_prog.get_uni_loc("viewProjMatrix");
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
window::~window()
{}

void window::draw()
{
	glBindVertexArray(vao);
	m_prog.use();
	
	glUniformMatrix4fv(m_uni_mat, 1, GL_FALSE, glm::value_ptr(*m_viewprojmat));
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ele_buffer);
	
	glUniform4f(m_uni_color, 0.f, 0.f, 0.f, .25f);
	glDrawElements(
		GL_TRIANGLES,
		m_indices.size(),
		GL_UNSIGNED_INT,
		(void*)0
	);
}
