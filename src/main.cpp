#include <GLFW/glfw3.h>

int main(int argc, char **argv)
{
	GLFWwindow *win;
	
	if(!glfwInit())
		return -1;
	
	win = glfwCreateWindow(640, 480, "Hello Window", NULL, NULL);
	if(!win) {
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(win);
	
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
