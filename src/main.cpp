#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <stdio.h>

#define GL_MAJOR 3
#define GL_MINOR 2

int main(int argc, char **argv)
{
	GLFWwindow *win;
	
	if(!glfwInit())
		return -1;
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_MINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
	win = glfwCreateWindow(640, 480, "Hello Window", NULL, NULL);
	if(!win) {
		glfwTerminate();
		printf("Could not create window!\n");
		return -1;
	}
	
	glfwMakeContextCurrent(win);
	
	GLenum err = glewInit();
	if(GLEW_OK != err) {
		glfwTerminate();
		printf("GLEW error: %s.\n", glewGetErrorString(err));
		return -1;
	}
	
	printf("OpenGL Version: %s.\n", glGetString(GL_VERSION));
	printf("GLEW Version:   %s.\n", glewGetString(GLEW_VERSION));
	
	while(!glfwWindowShouldClose(win)) {
		// render
		
		// swap
		glfwSwapBuffers(win);
		
		// poll
		glfwPollEvents();
	}
	
	glfwTerminate();
	return 0;
}
