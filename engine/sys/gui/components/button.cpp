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
	glBindVertexArray(m_vao);
	
		m_prog.use();
		glUniformMatrix4fv(m_uni_mat, 1, GL_FALSE, glm::value_ptr(*m_layout->m_viewprojmat));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
	glBindVertexArray(0);
	
	for(auto& c : m_children) {
		c->draw();
	}
	
}
bool button::mouse_in()
{
	return (m_layout->m_mouse->x > m_pos.x && m_layout->m_mouse->x < (m_pos.x + m_size.x) && m_layout->m_mouse->y > m_pos.y && m_layout->m_mouse->y < (m_pos.y + m_size.y));
}
void button::update()
{
	bool _mouse_in = mouse_in();

	// check mouse hovering
	if(_mouse_in) {
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
void button::handle_event()
{
	bool _mouse_in = mouse_in();
	
	event_t *_ev = m_layout->m_event;

	switch(_ev->m_channel) {
	case ev_channel::INPUT_MOUSE_BTN:
		auto ev = static_cast<events::input_mouse_btn*>(_ev);
		switch(ev->m_button) {
		case GLFW_MOUSE_BUTTON_1:
			if(ev->m_action == GLFW_PRESS)
				if(_mouse_in)
					handle_click();
			break;
		}
		break;
	}
}
void button::handle_click()
{
	static const std::string name = "lclick";

	if(m_cbacks.find(name) == m_cbacks.end())
		return;
	
	m_cbacks["lclick"]();
}

void button::upload()
{
	const float w = m_size.x, h = m_size.y;
	m_vbodat[0].vert = glm::vec2(0.f, 0.f);  // top left
	m_vbodat[0].col = m_col;
	m_vbodat[1].vert = glm::vec2(0.f, h);    // bott. left
	m_vbodat[1].col = m_col;
	m_vbodat[2].vert = glm::vec2(w, 0.f);    // top right
	m_vbodat[2].col = m_col;
	m_vbodat[3].vert = glm::vec2(w, h);      // bott. right
	m_vbodat[3].col = m_col;
	
	for(vertex& v : m_vbodat) {
		v.vert += m_pos;
	}
	
	std::array<GLuint, 6> indices = {{
		0, 1, 3,
		3, 2, 0
	}};
	
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);
	
	glBindVertexArray(m_vao);
	
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vbodat.size() * sizeof(vertex), &m_vbodat[0], GL_STATIC_DRAW);
		m_prog.set_attrib_ptr("position", 2, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
		m_prog.set_attrib_ptr("bg_color", 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)(sizeof(glm::vec2)));
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
	
	glBindVertexArray(0);
}
button* button::set_col(const glm::vec4 col)
{
	m_col = col;
	upload();
	return this;
}
