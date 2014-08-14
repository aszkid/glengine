#include "engine/sys/gui/components/window.hpp"

#include "engine/sys/gui/layout.hpp"

using namespace engine::gui::component;

window::window(layout *par_layout, glm::vec2 pos, glm::vec2 size)
	: engine::gui::base(par_layout)
{
	m_prog.add_shader(GL_FRAGMENT_SHADER, "../../../rundir/shaders/2dsurf_frag_bool.glsl");
	m_prog.add_shader(GL_VERTEX_SHADER, "../../../rundir/shaders/2dsurf_vert_bool.glsl");
	m_prog.link();
	
	// -----
	
	m_margin = 7.f;
	m_top_margin = m_margin * 3.25f;
	
	m_pos.x = 50.f;
	m_pos.y = 50.f;
	
	m_size.x = 640.f - m_margin*2;
	m_size.y = 360.f - m_margin - m_top_margin;
	
	m_vbodat[0].vert = glm::vec2(0.f, 0.f);
	m_vbodat[0].type = 1;
	m_vbodat[1].vert = glm::vec2(0.f, m_top_margin);
	m_vbodat[2].vert = glm::vec2(m_margin, 0.f);
	m_vbodat[3].vert = glm::vec2(m_margin, m_top_margin);
	m_vbodat[4].vert = glm::vec2(0.f, m_top_margin + m_size.y);
	m_vbodat[4].type = 0;
	m_vbodat[5].vert = glm::vec2(m_margin, m_top_margin + m_size.y);
	m_vbodat[6].vert = glm::vec2(0.f, m_margin + m_top_margin + m_size.y);
	m_vbodat[7].vert = glm::vec2(m_margin, m_margin + m_top_margin + m_size.y);
	m_vbodat[8].vert = glm::vec2(m_margin + m_size.x, m_margin + m_top_margin + m_size.y);
	m_vbodat[9].vert = glm::vec2(m_margin + m_size.x, m_top_margin + m_size.y);
	m_vbodat[10].vert = glm::vec2(m_margin*2 + m_size.x, m_margin + m_top_margin + m_size.y);
	m_vbodat[11].vert = glm::vec2(m_margin*2 + m_size.x, m_top_margin + m_size.y);
	m_vbodat[12].vert = glm::vec2(m_margin*2 + m_size.x, m_top_margin);
	m_vbodat[13].vert = glm::vec2(m_margin + m_size.x, m_top_margin);
	m_vbodat[14].vert = glm::vec2(m_margin*2 + m_size.x, 0.f);
	m_vbodat[15].vert = glm::vec2(m_margin + m_size.x, 0.f);
	
	static const std::array<uint, 8> topbar = {{1, 2, 3, 12, 13, 14, 15}};
	static const std::array<uint, 8> content = {{5, 6, 7, 8, 9, 10, 11}};
	
	for(size_t i : topbar) {
		m_vbodat[i].type = m_vbodat[0].type;
	}
	for(size_t i : content) {
		m_vbodat[i].type = m_vbodat[4].type;
	}
	
	for(auto& v : m_vbodat) {
		LOG("DEBUG-win", v.type);
	}
	
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
	
	for(size_t i = 0; i < m_vbodat.size(); i++) {
		m_vbodat[i].vert.x += m_pos.x;
		m_vbodat[i].vert.y += m_pos.y;
	}
	
	// ----
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	// fill data
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vbodat.size() * sizeof(vbo_data), &m_vbodat[0], GL_STATIC_DRAW);
	
	// fill indices
	glGenBuffers(1, &m_ele_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ele_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

	// ----
	
	m_prog.set_attrib_ptr("position", 2, GL_FLOAT, GL_FALSE, sizeof(vbo_data), 0);
	m_prog.set_attrib_ptr("surfType", 1, GL_INT, GL_FALSE, sizeof(vbo_data), (void*)sizeof(glm::vec2));
	
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
	
	glUniformMatrix4fv(m_uni_mat, 1, GL_FALSE, glm::value_ptr(*m_layout->m_viewprojmat));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ele_buffer);
	
	glDrawElements(
		GL_TRIANGLES,
		m_indices.size(),
		GL_UNSIGNED_INT,
		(void*)0
	);
}

void window::update()
{
	glm::vec2& pos = m_layout->m_mouse->m_pos;
	if((pos.x > m_vbodat[0].vert.x) && (pos.x < m_vbodat[12].vert.x) && (pos.y > m_vbodat[0].vert.y) && (pos.y < m_vbodat[1].vert.y)) {
		
	}
}
