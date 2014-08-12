#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <LuaState.h>

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <thread>

#include <engine/globals.hpp>
#include <engine/event_manager.hpp>
#include <engine/core.hpp>

#include <engine/sys/input.hpp>
#include <engine/sys/gui.hpp>

#include <engine/tools/shader.hpp>

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


void terminate(int ret, engine::core& c)
{
	c.shut_down();
	glfwTerminate();
	exit(ret);
}


engine::event_manager_ptr engine::ev_mngr;

int main(int argc, char** argv)
{
	std::map<int,int> hints;
	GLFWwindow *win;
	GLenum err;
	double ftime, nftime, time, ntime;
	
	
	lua::State base_cfg;
	try {
		base_cfg.doFile("../../../rundir/config.lua");
	} catch(lua::RuntimeError& err) {
		LOG("FATAL-lua", "'" << err.what() << "'.");
		return -1;
	}
	
	
	engine::sys_gui* gui;
	
	// Initialize the event manager
	engine::ev_mngr = engine::event_manager_ptr(new engine::event_manager());
	// Create a core instance
	engine::core core(std::vector<std::string>(argv, argv+argc));
	
	// ---- Initialize window and GL context
	glfwSetErrorCallback(glfw_err_callback);
	if(!glfwInit()) {
		LOG("FATAL", "Could not initialize GLFW!");
		terminate(-1, core);
	}
	
	float gl_v = float(base_cfg["gl_v"]["major"]) + float(base_cfg["gl_v"]["minor"]) / 10.0f;
	if(gl_v < 3.2f) {
		LOG("ERROR-cfg", "OpenGL version provided (" << gl_v << ") is not supported! OpenGL >=3.2 required.");
		terminate(-1, core);
	}
	
	// Set window creation hints
	hints[GLFW_CONTEXT_VERSION_MAJOR] = base_cfg["gl_v"]["major"];
	hints[GLFW_CONTEXT_VERSION_MINOR] = base_cfg["gl_v"]["minor"];
	hints[GLFW_OPENGL_PROFILE] = GLFW_OPENGL_CORE_PROFILE;
	hints[GLFW_OPENGL_FORWARD_COMPAT] = GL_TRUE;
	//hints[GLFW_RESIZABLE] = GL_FALSE;
	glfw_set_win_hints(hints);
	
	// Create window and set it to be the active context
	win = glfwCreateWindow(base_cfg["win_s"]["x"], base_cfg["win_s"]["y"], "OpenMilSim", NULL, NULL);
	glfwMakeContextCurrent(win);
	if(!win) {
		LOG("FATAL", "Could not create window!");
		terminate(-1, core);
	}
	
	// Initialize GLEW, and thus load GL function pointers
	err = glewInit();
	if(GLEW_OK != err) {
		LOG("GLEW_ERR", "'" << glewGetErrorString(err) << "'.");
		terminate(-1, core);
	}
	
	LOG("INFO", std::thread::hardware_concurrency() << " concurrent threads supported.");
	LOG("INFO", "OpenGL Version: " << glGetString(GL_VERSION));
	LOG("INFO", "GLEW Version:   " << glewGetString(GLEW_VERSION));
	
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
		terminate(-1, core);
	}
	
	// Attach input callbacks to input functions that will generate event messages
	engine::sys_input_attach(win);
	
	// ---- Quaid, start the reactor!
	core.bootstrap();
	
	// Load GUI layouts (future: on demand, script based?)
	auto pause = gui->new_layout();
	pause->add_component(new engine::gui::component::button());
	
	float r, g, b;
	r = 30 / 255.f;
	g = 30 / 255.f;
	b = 30 / 255.f;
	
	// ---- CONTROL THE MAIN LOOP RIGHT HERE (somehow)
	ftime = nftime = time = ntime = glfwGetTime();
	while(!glfwWindowShouldClose(win)) {
		ftime = nftime;
	
		// render
		glClearColor(r, g, b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
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
	terminate(EXIT_SUCCESS, core);
	
	return 0;
}

