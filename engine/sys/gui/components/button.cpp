#include "engine/sys/gui/components/button.hpp"

#include "engine/sys/gui/layout.hpp"

using namespace engine::gui::component;

button::button(layout *par_layout, glm::vec2 pos, glm::vec2 size)
	: engine::gui::base(par_layout)
{
	m_prog.add_shader(GL_FRAGMENT_SHADER, "../../../rundir/shaders/2dsurf_frag.glsl");
	m_prog.add_shader(GL_VERTEX_SHADER, "../../../rundir/shaders/2dsurf_vert.glsl");
	m_prog.link();
	
}
button::~button()
{}

void button::draw()
{
	
}
void button::update()
{}
