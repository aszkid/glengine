#include "engine/sys/input.hpp"

using namespace engine;


void input_callback::key_c(GLFWwindow *win, int key, int scancode, int action, int mods)
{
}
void input_callback::char_c(GLFWwindow *win, unsigned int key)
{
}
void input_callback::mouse_btn_c(GLFWwindow *win, int button, int action, int mods)
{
}


void engine::sys_input_attach(GLFWwindow *win)
{
	glfwSetKeyCallback(win, input_callback::key_c);
	glfwSetCharCallback(win, input_callback::char_c);
	glfwSetMouseButtonCallback(win, input_callback::mouse_btn_c);
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
