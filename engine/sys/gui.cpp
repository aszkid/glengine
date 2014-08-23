#include "engine/sys/gui.hpp"

using namespace engine;

sys_gui::sys_gui(GLFWwindow *win)
	: m_win(win)
{}
sys_gui::~sys_gui()
{}

void sys_gui::init()
{
	// initial view setup, otherwise the viewport is 0,0 and nothing is drawn until a window size event is received!
	glfwGetWindowSize(m_win, &m_viewport.x, &m_viewport.y);
	update_view();
}
void sys_gui::shut_down()
{}
void sys_gui::update(float dt)
{}

void sys_gui::update_view()
{
	glViewport(0, 0, m_viewport.x, m_viewport.y);
	m_viewprojmat = glm::ortho(0.f, float(m_viewport.x), float(m_viewport.y), 0.f);
}
void sys_gui::handle_event(event_t *event)
{
	switch(event->m_channel) {
	case INPUT_KEY: {
		auto ev = static_cast<events::input_key*>(event);
		if(ev->m_key == GLFW_KEY_H) {
			switch(ev->m_action) {
			case GLFW_PRESS: {
				glDisable(GL_BLEND);
				break;
			}
			case GLFW_RELEASE: {
				glEnable(GL_BLEND);
				break;
			}}
		}
		
		break;
	}
	case EXIT: {
		// should we really do something here?
		
		break;
	}
	case INPUT_WIN_SIZE: {
		auto ev = static_cast<events::input_win_size*>(event);
		m_viewport.x = ev->m_x; m_viewport.y = ev->m_y;
		update_view();
		
		break;
	}
	case INPUT_MOUSE_BTN: {
		auto ev = static_cast<events::input_mouse_btn*>(event);
		switch(ev->m_button) {
		case GLFW_MOUSE_BUTTON_1: {
			m_mouse.m_lclick = (ev->m_action == GLFW_PRESS);
			break;
		}
		case GLFW_MOUSE_BUTTON_2: {
			m_mouse.m_rclick = (ev->m_action == GLFW_PRESS);
			break;
		}
		default:
			break;
		}
		
		break;
	}
	case INPUT_CURSOR_POS: {
		auto ev = static_cast<events::input_cursor_pos*>(event);
		m_mouse.m_pos.x = ev->m_x; m_mouse.m_pos.y = ev->m_y;
		
		break;
	}
	default:
		break;
	}
	
	// update children... maybe?
}

sys_gui::layout_handle sys_gui::new_layout()
{
	m_layouts.emplace_back(new gui::layout(&m_viewport, &m_viewprojmat, &m_mouse));
	return m_layouts.back().get();
}

glm::ivec2* sys_gui::get_viewport()
{
	return &m_viewport;
}
