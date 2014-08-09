#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>

#include <stdio.h>
#include <string>

#include "oms/screen.hpp"

#define GL_MAJOR 3
#define GL_MINOR 2
#define WIN_WIDTH  640
#define WIN_HEIGHT 480

#define MK_SHADER_SRC(v, src) "#version " #v "\n" #src

std::string charbuff;

void flush_charbuff()
{
	printf("MESSAGE: %s\n", charbuff.c_str());
	charbuff.clear();
}

void key_callback(GLFWwindow *win, int key, int scancode, int action, int mods)
{
	if(action == GLFW_PRESS) {
		switch(key) {
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(win, GL_TRUE);
			break;
		case GLFW_KEY_ENTER:
			flush_charbuff();
			break;
		}
	}
}

void winsize_callback(GLFWwindow *win, int x, int y)
{
	glViewport(0, 0, x, y);
}

void char_callback(GLFWwindow *win, unsigned int c)
{
	charbuff += c;
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

int main()
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
	glfwSetCharCallback(win, char_callback);
	glfwSetWindowSizeCallback(win, winsize_callback);
	
	glfwSwapInterval(0);
	//glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	
	double time = glfwGetTime(), ntime, ftime, nftime;
	glm::vec2 mpos;
	ftime = nftime = time;
	
	// opengl vars and such
	/*GLfloat verts[] = {
		+0.0f, +1.0f,
		-1.0f, -1.0f,
		+1.0f, -1.0f
	};*/
	
	glm::mat3x2 mat;
	mat[0] = glm::vec2(+0.0f, +1.0f);
	mat[1] = glm::vec2(-1.0f, -1.0f);
	mat[2] = glm::vec2(+1.0f, -1.0f);
	
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mat), glm::value_ptr(mat), GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	
	oms::screen s;
	
	while(!glfwWindowShouldClose(win)) {
		ftime = nftime;
		
		// render stuff
		// ------
		// setup3d() render3d()
		// setup2d() render2d()
		// ------
		
		glClearColor(0.1, 0.1, 0.1, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		// swap buffers
		glfwSwapBuffers(win);
		// ------
		
		// poll events
		glfwPollEvents();
		mpos = mouse_pos(win);
		ntime = nftime = glfwGetTime();
		
		if((ntime - time) > 2) {
			time = ntime;
			printf("FPS: %i.\n", int(1 / (nftime - ftime)));
		}
	}
	
	glfwTerminate();
	return 0;
}
