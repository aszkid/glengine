#include "engine/sys/input.hpp"

using namespace engine;


void input_callback::key_c(GLFWwindow *win, int key, int scancode, int action, int mods)
{
	ev_mngr->broadcast(event_t(ev_channel::INPUT_KEY));
}
void input_callback::char_c(GLFWwindow *win, unsigned int key)
{
	ev_mngr->broadcast(event_t(ev_channel::INPUT_CHAR));
}
void input_callback::mouse_btn_c(GLFWwindow *win, int button, int action, int mods)
{
	ev_mngr->broadcast(event_t(ev_channel::INPUT_MOUSE_BTN));
}
void input_callback::win_size_c(GLFWwindow *win, int x, int y)
{
	ev_mngr->broadcast(event_t(ev_channel::INPUT_WIN_SIZE));
}


void engine::sys_input_attach(GLFWwindow *win)
{
	glfwSetKeyCallback(win, input_callback::key_c);
	glfwSetCharCallback(win, input_callback::char_c);
	glfwSetMouseButtonCallback(win, input_callback::mouse_btn_c);
	glfwSetWindowSizeCallback(win, input_callback::win_size_c);
}

sys_input::sys_input()
{}
sys_input::~sys_input()
{}

void sys_input::init()
{}
void sys_input::shut_down()
{}
void sys_input::update(float dt)
{}
