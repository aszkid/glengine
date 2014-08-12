#include "engine/sys/gui/components/button.hpp"

using namespace engine::gui::component;

button::button()
{
	m_prog.add_shader(GL_FRAGMENT_SHADER, "../../../rundir/shaders/button_frag.glsl");
	m_prog.add_shader(GL_VERTEX_SHADER, "../../../rundir/shaders/button_vert.glsl");
	m_prog.link();
}
button::~button()
{}

void button::draw()
{}
