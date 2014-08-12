#include "engine/sys/gui.hpp"

using namespace engine;

sys_gui::sys_gui()
{}
sys_gui::~sys_gui()
{}

void sys_gui::init()
{}
void sys_gui::shut_down()
{}
void sys_gui::update(float dt)
{}


void sys_gui::handle_event(event_t event)
{
	switch(event.m_channel) {
	case INPUT_WIN_SIZE:
		//glViewport(0, 0, x, y);
		break;
	case INPUT_MOUSE_BTN:
		break;
	default:
		break;
	}
}
void sys_gui::draw()
{
	glClearColor(0.1, 0.1, 0.1, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}


sys_gui::layout_handle sys_gui::new_layout()
{
	m_layouts.emplace_back(new gui::layout());
	return m_layouts.back().get();
}
