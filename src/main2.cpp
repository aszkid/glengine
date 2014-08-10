#include <engine/globals.hpp>
#include <engine/core.hpp>

#include <engine/sys/cfg.hpp>
#include <engine/sys/log.hpp>
/*#include <engine/sys/input.hpp>
#include <engine/sys/render.hpp>*/

/*#include <GL/glew.h>
#include <GLFW/glfw3.h>*/

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

#define SYS_UPTR(s) std::unique_ptr<engine::system>(new s)

enum glfw_Callbacks {
	ERROR,
	KEY,
	CHAR,
	WIN_SIZE
};

int main(int argc, char** argv)
{
	using std::cout;
	using std::endl;

	engine::core core(std::vector<std::string>(argv, argv+argc));
	
	// ---- Create all systems, and add them to the core vector
	try {
		core.add_sys(engine::SYSid::cfg, SYS_UPTR(engine::sys_cfg()));
		// engine::sys_cfg provides an interface to access configuration files
		// from all core systems.
		
		core.add_sys(engine::SYSid::log, SYS_UPTR(engine::sys_log()));
		// engine::sys_log
		
		/*core.add_sys(SYSid::input, SYS_UPTR(engine::sys_input()));
		// engine::sys_input populates function dispatchers that broadcast input
		// data to all core systems.
		
		core.add_sys(SYSid::render, SYS_UPTR(engine::sys_render()));*/
		// engine::sys_render
	} catch(std::runtime_error& ex) {
		LOG("FATAL", "Exception at 'engine::system' creation: '" << ex.what() << "'.");
		core.shut_down();
		return -1;
	}
	
	// ---- Initialize window and GL context
	//GLFWwindow *win;


	// ---- Quaid, start the reactor!
	core.bootstrap();
	
	// ---- We're done.
	core.shut_down();
	
	return 0;
	
	// ----------------------------

	/*GLFWwindow *win;
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
	glfwTerminate();*/
	
	return 0;
}
