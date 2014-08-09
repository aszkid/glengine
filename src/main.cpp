#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <stdio.h>

#define GL_MAJOR 3
#define GL_MINOR 2

#define WIN_WIDTH  640
#define WIN_HEIGHT 480

void key_callback(GLFWwindow *win, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(win, GL_TRUE);
}

glm::vec2 mouse_pos(GLFWwindow *win)
{
	glm::vec2 ret;
	double x, y;
	glfwGetCursorPos(win, &x, &y);

	ret.x = x / float(WIN_WIDTH);
	ret.y = y / float(WIN_HEIGHT);
	
	return ret;
}

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
	
	win = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Hello Window", NULL, NULL);
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
	
	glfwSetKeyCallback(win, key_callback);
	
	double time = glfwGetTime(), ntime;
	glm::vec2 mpos;
	
	while(!glfwWindowShouldClose(win)) {
		// render stuff
		// ------
		// setup3d() render3d()
		// setup2d() render2d()
		// ------
		
		// swap buffers
		glfwSwapBuffers(win);
		// ------
		
		// poll events
		glfwPollEvents();
		
		ntime = glfwGetTime();
		if((ntime - time) > 0.5) {
			time = ntime;
			mpos = mouse_pos(win);
			printf("X: %f | Y: %f\n", mpos.x, mpos.y);
		}
		// ------
	}
	
	glfwTerminate();
	return 0;
}
