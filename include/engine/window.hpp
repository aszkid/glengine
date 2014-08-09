#pragma once

#include <map>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace engine {

	static void callback_winSize(GLFWwindow *win, int x, int y);
	

class window {
	GLFWwindow *handle;

	
public:
	window();
	~window();
	
	void init(std::map<int,int> hints, int x, int y, std::string title);
	
	// callbacks
	void callback_winSize(int x, int y);
};

}
