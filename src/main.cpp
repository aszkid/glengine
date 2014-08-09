#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

int main(int argc, char **argv)
{
	GLFWwindow *win;
	
	if(!glfwInit())
		return -1;
	
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
		printf("Could not initialize GLEW!\n");
		return -1;
	}
	
	
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
