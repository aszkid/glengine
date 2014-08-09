#include "engine/window.hpp"

using namespace engine;

// GLFW CALLBACKS
static void engine::callback_winSize(GLFWwindow *gwin, int x, int y)
{
	window *win = reinterpret_cast<window*>(glfwGetWindowUserPointer(gwin));
	win->callback_winSize(x, y);
}

window::window()
{}

window::~window()
{}

void window::init(std::map<int,int> hints, int x, int y, std::string title)
{
	for(auto it = hints.begin(); it != hints.end(); it++) {
		glfwWindowHint(it->first, it->second);
	}
	
	handle = glfwCreateWindow(x, y, title.c_str(), NULL, NULL);
	
	glfwSetWindowUserPointer(handle, this);
	glfwSetWindowSizeCallback(handle, engine::callback_winSize);
	
	glfwMakeContextCurrent(handle);
	GLenum err = glewInit();
	if(GLEW_OK != err) {
		glfwTerminate();
		printf("GLEW error: %s.\n", glewGetErrorString(err));
		throw std::exception();
	}
}

void window::callback_winSize(int x, int y)
{
	printf("Wow, window resized: (%i, %i).\n", x, y);
	glViewport(0, 0, x, y);
}
