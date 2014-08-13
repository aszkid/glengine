#include "engine/sys/gui/components/window.hpp"

using namespace engine::gui::component;

window::window(glm::ivec2 *viewport, glm::mat4 *viewprojmat, glm::vec2 pos, glm::vec2 size)
	: engine::gui::base(viewport, viewprojmat)
{
	m_prog.add_shader(GL_FRAGMENT_SHADER, "../../../rundir/shaders/2dsurf_frag.glsl");
	m_prog.add_shader(GL_VERTEX_SHADER, "../../../rundir/shaders/2dsurf_vert.glsl");
	m_prog.link();
	
	// -----
	
	m_margin = 0.05f;
	
	m_pos.x = -1.0f;
	m_pos.y = -1.0f;
	
	m_size.x = 250 / m_viewport->x;
	m_size.y = 300 / m_viewport->y;
	
	m_indices = {
		0, 1, 2,
		2, 1, 3/*,
		3, 1, 4,
		3, 4, 5*/
	};	
	/*std::vector<GLfloat> vertices = {
		0.f, 0.f,			// 0
		0.f, m_margin,			// 1
		m_margin, 0.f,			// 2
		m_margin, m_margin,		// 3
		0.f, m_margin + m_size.y,	// 4
		m_margin, m_margin + m_size.y	// 5
	};*/
	
	std::vector<GLfloat> vertices = {
		0.f, 0.f,
		0.f, 20.f,
		20.f, 0.f,
		20.f, 20.f
	};
	
	/*std::vector<GLfloat> vertices = {
		-1.0f, 1.0f,
		-1.0f, 0.95f,
		-0.95f, 1.0f,
		-0.95f, 0.95f,
		-1.0f, 0.2f,
		-0.95f, 0.2f
	};*/
	
	/*for(size_t i = 0; i < vertices.size(); i += 2) {
		vertices[i]   += m_pos.x;
		vertices[i+1] += m_pos.y;
	}*/
	
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
	glUniform4f(m_uni_color, 1.0f, 1.0f, 1.0f, 1.0f);
	glUniformMatrix4fv(m_uni_mat, 1, GL_FALSE, glm::value_ptr(*m_viewprojmat));
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ele_buffer);
	glDrawElements(
		GL_TRIANGLES,      // mode
		m_indices.size(),    // count
		GL_UNSIGNED_INT,   // type
		(void*)0           // element array buffer offset
	);
}
