#include "engine/sys/gui/components/button.hpp"

#include "engine/sys/gui/layout.hpp"

using namespace engine::gui::component;

button::button(layout *par_layout, glm::vec2 pos, glm::vec2 size)
	: engine::gui::base(par_layout)
{
	m_label = static_cast<label*>(add_child(new label(m_layout, engine::cstr_to_wstr("LPLAY").c_str(), 35, pos)));

	m_prog.add_shader(GL_FRAGMENT_SHADER, "../../../rundir/shaders/test_frag.glsl");
	m_prog.add_shader(GL_VERTEX_SHADER, "../../../rundir/shaders/test_vert.glsl");
	m_prog.link();
	
	const float w = m_label->m_width, h = 35.f;
	std::array<vertex, 4> m_vbodat;
	m_vbodat[0].vert = glm::vec2(0.f, 0.f);
	m_vbodat[1].vert = glm::vec2(0.f, h);
	m_vbodat[2].vert = glm::vec2(w, 0.f);
	m_vbodat[3].vert = glm::vec2(w, h);
	
	for(vertex& v : m_vbodat) {
		v.vert += pos;
	}
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	glBufferData(GL_ARRAY_BUFFER, m_vbodat.size() * sizeof(vertex), &m_vbodat[0], GL_STATIC_DRAW);

	m_prog.set_attrib_ptr("position", 2, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
	m_uni_mat = m_prog.get_uni_loc("viewProjMatrix");
}
button::~button()
{}

void button::draw()
{
	m_prog.use();
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glUniformMatrix4fv(m_uni_mat, 1, GL_FALSE, glm::value_ptr(*m_layout->m_viewprojmat));
	m_prog.set_attrib_ptr("position", 2, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
	
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
	for(auto& c : m_children) {
		c->draw();
	}
}
void button::update()
{
	if(!m_dirty)
		return;
	
	// update vbo (change in position, color, etc...)
}
