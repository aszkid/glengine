//#include <engine/core.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <map>
#include <string>
#include <iostream>ssss

#define LOG(x) std::cout << "[LOG] " << x << std::endl

static void err_callback(int err, const char *msg)
{
	LOG("[" << err << "] " << msg);
}

int main()
{
	//engine::core core;

	GLFWwindow *win;
	if(!glfwInit())
		return -1;
		
	glfwSetErrorCallback(err_callback);
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
	win = glfwCreateWindow(640, 480, "OpenMilSim", NULL, NULL);
	glfwMakeContextCurrent(win);
	
	//glfwSetWindowUserPointer(win, &core);
	if(!win) {
		glfwTerminate();
		LOG("Could not create window!");
		return -1;
	}
	
	GLenum err = glewInit();
	if(GLEW_OK != err) {
		glfwTerminate();
		LOG("GLEW error: " << glewGetErrorString(err));
		return -1;
	}
	
	glfwDestroyWindow(win);
	glfwTerminate();
	return 0;
}
