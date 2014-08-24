#include "engine/sys/gui/components/button.hpp"

#include "engine/sys/gui/layout.hpp"

using namespace engine::gui::component;

button::button(layout *par_layout, const std::string text, glm::vec2 pos, int margin, glm::vec2 size, glm::vec4 col)
	: engine::gui::base(par_layout), m_size(size), m_pos(pos)
{
	static const char* deffont = "fira-sans/FiraSans-ExtraLight.otf";
	static const int fsize = 30;

	m_label = add_child<label>(text, fsize, m_pos + glm::vec2(margin), glm::vec4(1), deffont);

	if(m_size.x != -1) {
		m_label->set_pos(glm::vec2(
			(m_size.x - m_label->m_size.x)/2.0 + m_pos.x,
			m_label->m_pos.y
		));
	} else {
		m_size.x = m_label->m_size.x + margin*2;
	}
	
	if(m_size.y != -1) {
		m_label->set_pos(glm::vec2(
			m_label->m_pos.x,
			(m_size.y - m_label->m_size.y)/2.0 + m_pos.y
		));
	} else {
		m_size.y = m_label->m_size.y + margin*2;
	}

	m_prog.add_shader(GL_FRAGMENT_SHADER, "../../../rundir/shaders/test_frag.glsl");
	m_prog.add_shader(GL_VERTEX_SHADER, "../../../rundir/shaders/test_vert.glsl");
	m_prog.link();
	
	const float w = m_size.x, h = m_size.y;
	std::array<vertex, 4> m_vbodat;
	m_vbodat[0].vert = glm::vec2(0.f, 0.f);
	m_vbodat[0].col = col;
	m_vbodat[1].vert = glm::vec2(0.f, h);
	m_vbodat[1].col = col;
	m_vbodat[2].vert = glm::vec2(w, 0.f);
	m_vbodat[2].col = col;
	m_vbodat[3].vert = glm::vec2(w, h);
	m_vbodat[3].col = col;
	
	for(vertex& v : m_vbodat) {
		v.vert += m_pos;
	}
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	glBufferData(GL_ARRAY_BUFFER, m_vbodat.size() * sizeof(vertex), &m_vbodat[0], GL_STATIC_DRAW);

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
	m_prog.set_attrib_ptr("bg_color", 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)(sizeof(glm::vec2)));
	
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
	for(auto& c : m_children) {
		c->draw();
	}
}
void button::update()
{
	// update vbo (change in position, color, etc...)
}
