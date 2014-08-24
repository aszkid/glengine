#include "engine/sys/gui/components/button.hpp"

#include "engine/sys/gui/layout.hpp"

using namespace engine::gui::component;

button::button(layout *par_layout, const std::string text, glm::vec2 pos, int margin, glm::vec2 size, glm::vec4 col)
	: engine::gui::base(par_layout), m_state(btn_state::NONE), m_pos(pos), m_size(size), m_col(col)
{
	static const char* deffont = "fira-sans/FiraSans-ExtraLight.otf";
	static const int fsize = 30;

	m_label = add_child<label>(text, fsize, m_pos + glm::vec2(margin), glm::vec4(1), deffont);

	if(m_size.x != -1) {
		m_label->set_pos(glm::vec2(
			(m_size.x - m_label->m_bbox.x)/2.0 + m_pos.x,
			m_label->m_pos.y
		));
	} else {
		m_size.x = m_label->m_bbox.x + margin*2;
	}
	
	if(m_size.y != -1) {
		m_label->set_pos(glm::vec2(
			m_label->m_pos.x,
			(m_size.y - m_label->m_bbox.y)/2.0 + m_pos.y
		));
	} else {
		m_size.y = m_label->m_bbox.y + margin*2;
	}

	m_prog.add_shader(GL_FRAGMENT_SHADER, "../../../rundir/shaders/test_frag.glsl");
	m_prog.add_shader(GL_VERTEX_SHADER, "../../../rundir/shaders/test_vert.glsl");
	m_prog.link();
	
	upload();

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
	glm::vec2 mpos = m_layout->m_mouse->m_pos;
	
	// check mouse hovering
	if(mpos.x > m_pos.x && mpos.x < (m_pos.x + m_size.x) && mpos.y > m_pos.y && mpos.y < (m_pos.y + m_size.y)) {
		// hover-in
		if(m_state != btn_state::HOVER) {
			m_state = btn_state::HOVER;
			set_col(glm::vec4(.2, .2, .2, m_col.a));
			upload();
		}		
	} else {
		// hover-out
		if(m_state == btn_state::HOVER) {
			m_state = btn_state::NONE;
			set_col(glm::vec4(.1, .1, .1, m_col.a));
			upload();
		}
	}
	
}


void button::upload()
{
	const float w = m_size.x, h = m_size.y;
	m_vbodat[0].vert = glm::vec2(0.f, 0.f);
	m_vbodat[0].col = m_col;
	m_vbodat[1].vert = glm::vec2(0.f, h);
	m_vbodat[1].col = m_col;
	m_vbodat[2].vert = glm::vec2(w, 0.f);
	m_vbodat[2].col = m_col;
	m_vbodat[3].vert = glm::vec2(w, h);
	m_vbodat[3].col = m_col;
	
	for(vertex& v : m_vbodat) {
		v.vert += m_pos;
	}
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	glBufferData(GL_ARRAY_BUFFER, m_vbodat.size() * sizeof(vertex), &m_vbodat[0], GL_STATIC_DRAW);
}
button* button::set_col(const glm::vec4 col)
{
	m_col = col;
	upload();
	return this;
}
