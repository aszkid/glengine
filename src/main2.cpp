#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

#include <engine/globals.hpp>
#include <engine/event_manager.hpp>
#include <engine/core.hpp>

#include <engine/sys/input.hpp>
#include <engine/sys/gui.hpp>

#define SYS_MKPTR(s) std::shared_ptr<engine::system>(new s)
#define SYS_SUBSCRIBE(s, ch) engine::ev_mngr->subscribe(engine::subscription(ch, core.get_sys_raw(s)));

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

engine::event_manager_ptr engine::ev_mngr;

int main(int argc, char** argv)
{
	int ret = 0;
	std::map<int,int> hints;
	GLFWwindow *win;
	GLenum err;
	double ftime, nftime, time, ntime;
	
	engine::sys_gui* gui;
	
	// Initialize the event manager
	engine::ev_mngr = engine::event_manager_ptr(new engine::event_manager());
	// Create a core instance
	engine::core core(std::vector<std::string>(argv, argv+argc));
	
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
	//hints[GLFW_RESIZABLE] = GL_FALSE;
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
	
	// ---- Create all systems, and add them to the core vector
	try {
		core.add_sys(engine::SYSid::input, SYS_MKPTR(engine::sys_input));
		
		core.add_sys(engine::SYSid::gui, SYS_MKPTR(engine::sys_gui));
		SYS_SUBSCRIBE(engine::SYSid::gui, 
			engine::ev_channel::INPUT_MOUSE_BTN | engine::ev_channel::INPUT_CHAR | engine::ev_channel::INPUT_WIN_SIZE
		);
		gui = dynamic_cast<engine::sys_gui*>(core.get_sys_raw(engine::SYSid::gui));
		
		
	} catch(std::runtime_error& ex) {
		LOG("FATAL", "Exception at 'engine::system' creation: '" << ex.what() << "'.");
		ret = -1;
		goto terminate;
	}
	
	// Attach input callbacks to input functions that will generate event messages
	engine::sys_input_attach(win);

	// ---- Quaid, start the reactor!
	core.bootstrap();
	
	// ---- CONTROL THE MAIN LOOP RIGHT HERE (somehow)
	ftime = nftime = time = ntime = glfwGetTime();
	while(!glfwWindowShouldClose(win)) {
		ftime = nftime;
	
		// render
		gui->draw();
		
		glfwSwapBuffers(win);
		
		// handle events
		glfwPollEvents();
		
		// update
		core.update_all(0.5f);
		
		ntime = nftime = glfwGetTime();
		if((ntime - time) > 2) {
			time = ntime;
			LOG("INFO", "FPS: " << int(1 / (nftime - ftime)));
		}
	}
	
	// ---- We're done, thanks for your attention
terminate:
	core.shut_down();
	glfwTerminate();
	
	return ret;
}

