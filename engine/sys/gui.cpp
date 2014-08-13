#include "engine/sys/gui.hpp"

using namespace engine;

sys_gui::sys_gui(GLFWwindow *win)
	: m_active_layout(nullptr), m_win(win)
{}
sys_gui::~sys_gui()
{}

void sys_gui::init()
{
	if(FT_Init_FreeType(&m_ft)) {
		throw std::runtime_error("Could not initialize Freetype library!");
	}
	
	glfwGetWindowSize(m_win, &m_viewport.x, &m_viewport.y);
}
void sys_gui::shut_down()
{}
void sys_gui::update(float dt)
{}

void sys_gui::handle_event(event_t event)
{
	switch(event.m_channel) {
	case INPUT_WIN_SIZE:
		glfwGetWindowSize(m_win, &m_viewport.x, &m_viewport.y);
		glViewport(0, 0, m_viewport.x, m_viewport.y);
		
		break;
	case INPUT_MOUSE_BTN:
		break;
	default:
		break;
	}
}
void sys_gui::draw()
{
	/*glClearColor(0.1, 0.1, 0.1, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);*/
	if(m_active_layout == nullptr)
		return;
	
	m_active_layout->draw();
}

sys_gui::layout_handle sys_gui::new_layout()
{
	m_layouts.emplace_back(new gui::layout(&m_viewport));
	if(m_active_layout == nullptr) {
		m_active_layout = m_layouts.back().get();
		return m_active_layout;
	}
	return m_layouts.back().get();
}

FT_Face sys_gui::new_face(const char *filename)
{
	FT_Face face;
	if(FT_New_Face(m_ft, filename, 0, &face)) {
		throw std::runtime_error(MKSTR("Could not create face '" << filename << "'!"));
	}
	return face;
}
