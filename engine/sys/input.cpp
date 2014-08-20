#include "engine/sys/input.hpp"

using namespace engine;


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void input_callback::key_c(GLFWwindow *win, int key, int scancode, int action, int mods)
{
	ev_mngr->broadcast(new engine::events::input_key(ev_channel::INPUT_KEY, key, scancode, action, mods));
}
void input_callback::char_c(GLFWwindow *win, unsigned int key)
{
	ev_mngr->broadcast(new engine::events::input_char(ev_channel::INPUT_CHAR, key));
}
void input_callback::mouse_btn_c(GLFWwindow *win, int button, int action, int mods)
{
	ev_mngr->broadcast(new engine::events::input_mouse_btn(ev_channel::INPUT_MOUSE_BTN, button, action, mods));
}
void input_callback::win_size_c(GLFWwindow *win, int x, int y)
{
	ev_mngr->broadcast(new engine::events::input_win_size(ev_channel::INPUT_WIN_SIZE, x, y));
}
void input_callback::cursor_pos_c(GLFWwindow *win, double x, double y)
{
	ev_mngr->broadcast(new engine::events::input_cursor_pos(ev_channel::INPUT_CURSOR_POS, x, y));
}
void input_callback::win_close_c(GLFWwindow *win)
{
	ev_mngr->broadcast(new engine::events::exit(ev_channel::EXIT, 0));
}
#pragma GCC diagnostic pop

void engine::sys_input_attach(GLFWwindow *win)
{
	glfwSetKeyCallback(win, input_callback::key_c);
	glfwSetCharCallback(win, input_callback::char_c);
	glfwSetMouseButtonCallback(win, input_callback::mouse_btn_c);
	glfwSetWindowSizeCallback(win, input_callback::win_size_c);
	glfwSetCursorPosCallback(win, input_callback::cursor_pos_c);
	glfwSetWindowCloseCallback(win, input_callback::win_close_c);
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
