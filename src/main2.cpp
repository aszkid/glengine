#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

#include <engine/globals.hpp>
#include <engine/core.hpp>
#include <engine/event_manager.hpp>

#include <engine/sys/input.hpp>
#include <engine/sys/gui.hpp>

#define SYS_MKPTR(s) std::shared_ptr<engine::system>(new s())

void glfw_set_win_hints(const std::map<int,int> &hints)
{
	for(auto it = hints.begin(); it != hints.end(); it++) {
		glfwWindowHint(it->first, it->second);
	}
}
void glfw_err_callback(const int errcode, const char* msg)
{
	LOG("GLFW_ERR", "(id" << errcode << ") '" << msg << "'.");
}

int main(int argc, char** argv)
{
	int ret = 0;
	std::map<int,int> hints;
	GLFWwindow *win;
	GLenum err;
	
	engine::event_manager ev_manager;

	engine::core core(std::vector<std::string>(argv, argv+argc));
	
	// ---- Create all systems, and add them to the core vector
	try {
		core.add_sys(engine::SYSid::input, SYS_MKPTR(engine::sys_input));
		ev_manager.subscribe(engine::subscription(0 | 2 | 4, core.get_sys(engine::SYSid::input)));
		
		
	} catch(std::runtime_error& ex) {
		LOG("FATAL", "Exception at 'engine::system' creation: '" << ex.what() << "'.");
		ret = -1;
		goto terminate;
	}
	
	// ---- Initialize window and GL context
	glfwSetErrorCallback(glfw_err_callback);
	if(!glfwInit()) {
		LOG("FATAL", "Could not initialize GLFW!");
		ret = -1;
		goto terminate;
	}
	
	// Set window creation hints
	hints[GLFW_CONTEXT_VERSION_MAJOR] = 3;
	hints[GLFW_CONTEXT_VERSION_MINOR] = 2;
	hints[GLFW_OPENGL_PROFILE] = GLFW_OPENGL_CORE_PROFILE;
	hints[GLFW_OPENGL_FORWARD_COMPAT] = GL_TRUE;
	hints[GLFW_RESIZABLE] = GL_FALSE;
	glfw_set_win_hints(hints);
	
	// Create window and set it to be the active context
	win = glfwCreateWindow(640, 480, "OpenMilSim", NULL, NULL);
	glfwMakeContextCurrent(win);
	if(!win) {
		LOG("FATAL", "Could not create window!");
		ret = -1;
		goto terminate;
	}
	
	// Initialize GLEW, and thus load GL function pointers
	err = glewInit();
	if(GLEW_OK != err) {
		LOG("GLEW_ERR", "'" << glewGetErrorString(err) << "'.");
		ret = -1;
		goto terminate;
	}

	// ---- Quaid, start the reactor!
	core.bootstrap();
	
	// ---- CONTROL THE MAIN LOOP RIGHT HERE
	
	// ---- We're done, thanks for your attention
terminate:
	core.shut_down();
	glfwTerminate();
	
	return ret;
}

