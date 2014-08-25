#include <GL/glew.h>

// std includes
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <thread>
#include <typeinfo>
#include <csignal>
#include <chrono>
#include <ctime>
#include <locale>

// engine includes
#include <engine/globals.hpp>
#include <engine/event_manager.hpp>
#include <engine/config_manager.hpp>
#include <engine/log_manager.hpp>
#include <engine/core.hpp>

#include <engine/sys/input.hpp>
#include <engine/sys/gstate.hpp>
#include <engine/sys/gui.hpp>

// boost includes
#include <boost/filesystem/operations.hpp>
#include <boost/locale.hpp>

// game-specific states
#include "states/main_screen.hpp"


// macro heaven
#ifdef OS_LINUX
	#include <unistd.h> // geteuid
#endif

#define SYS_MKPTR(s) engine::sys_ptr(new s)
#define SYS_SUBSCRIBE(s, ch) engine::ev_mngr->subscribe(engine::subscription(ch, core->get_sys(s)));

// TODO: check why we can't use the 'log' alias
namespace loglev = engine::log;

void glfw_set_win_hints(const std::map<int,int> &hints)
{
	for(auto it = hints.begin(); it != hints.end(); it++) {
		glfwWindowHint(it->first, it->second);
	}
}
void glfw_err_callback(const int errcode, const char* msg)
{
	LOG("main", loglev::ERROR) << "GLFW_ERR: (id" << errcode << ") '" << msg << "'.";
}

// Manager declarations
EV_DECL();
CFG_DECL();
LOG_DECL();

// Core object: vital
std::unique_ptr<engine::core> core;

void cleanup()
{
	LOG("main", loglev::INFO) << "Cleanup...";
	glfwTerminate();
	engine::ev_mngr.reset();
	engine::cfg_mngr.reset();
	engine::log_mngr.reset();
	core.reset();
}
#define TERMINATE(val) cleanup(); return val;

/*void signal_handler(int code)
{
	LOG("main", loglev::INFO) << "Closing down (signal '" << code << "').";

	// ---
	// 1 - save game state or anything valuable
	// 2 - free core (and subsequently, all systems)
	// 3 - free managers
	// ---
	
	cleanup();	
	exit(-1);
}*/

void run()
{
	// set up signal handler
	// TODO
	//std::signal(SIGINT, signal_handler);
	
	std::map<int,int> hints;
	GLFWwindow *win;
	GLenum err;
	double ftime, nftime, time, ntime;

	// Set locale
	boost::locale::generator gen;
	std::locale loc = gen("en_US.UTF-8");
	std::locale::global(loc);
	
	// Initialize the managers
	engine::log_mngr = engine::log_manager_ptr(new engine::log_manager());
	engine::cfg_mngr = engine::config_manager_ptr(new engine::config_manager());
	engine::ev_mngr = engine::event_manager_ptr(new engine::event_manager(core.get()));
	
	// Construct all the loggers
	engine::log_mngr->make<engine::void_logger>("void"); // this is needed for conditional logging
	engine::log_mngr->make("main");
	engine::log_mngr->make("ev_mngr");
	engine::log_mngr->make("cfg_mngr");
	engine::log_mngr->make("log_mngr");
	engine::log_mngr->make("sys_gui");
	engine::log_mngr->make("sys_gstate");
	engine::log_mngr->make("core");
	engine::log_mngr->make("t_shader");

	// Preload our config files
	const char* p_core  = "../../../rundir/cfg/core.lua";
	auto& base_cfg = engine::cfg_mngr->get(p_core);
	auto gl_vt = base_cfg.get<sol::table>("gl_v");
	auto win_st = base_cfg.get<sol::table>("win_s");
	auto bg_ct = base_cfg.get<sol::table>("bg_c");

	// Initialize window and GL context
	glfwSetErrorCallback(glfw_err_callback);
	if(!glfwInit()) {
		LOG("main", loglev::FATAL) << "Could not initialize GLFW!";
		EXIT_EXCEPT(-1);
	}
	
	// Prepare a pointer to the systems
	engine::sys_gui* gui;
	engine::sys_gstate* gstate;
	
	
	float gl_v = int(gl_vt["major"]) + float(gl_vt["minor"]) / 10.0f;
	if(gl_v < 3.2f) {
		LOG("main", loglev::FATAL) << "OpenGL version provided (" << gl_v << ") is not supported! OpenGL >=3.2 required.";
		EXIT_EXCEPT(-1);
	}
	
	// Set window creation hints
	hints[GLFW_CONTEXT_VERSION_MAJOR] = gl_vt["major"];
	hints[GLFW_CONTEXT_VERSION_MINOR] = gl_vt["minor"];
	hints[GLFW_OPENGL_PROFILE] = GLFW_OPENGL_CORE_PROFILE;
	hints[GLFW_OPENGL_FORWARD_COMPAT] = GL_TRUE;
	hints[GLFW_RESIZABLE] = GL_FALSE;
	glfw_set_win_hints(hints);
	
	// Create window and set it to be the active context
	bool cfg_mon = base_cfg["fullscreen"];
	GLFWmonitor *monitor = (cfg_mon ? glfwGetPrimaryMonitor() : NULL);
	win = glfwCreateWindow(win_st["x"], win_st["y"], "OpenMilSim", monitor, NULL);
	glfwMakeContextCurrent(win);
	if(!win) {
		LOG("main", loglev::FATAL) << "Could not create window!";
		EXIT_EXCEPT(-1);
	}
	
	glGetError();
	// Initialize GLEW, and thus load GL function pointers
	err = glewInit();
	if(GLEW_OK != err) {
		LOG("main", loglev::FATAL) << "GLEW_ERR: '" << glewGetErrorString(err) << "'.";
		EXIT_EXCEPT(-1);
	}
	
	LOG("main", loglev::INFO) << std::thread::hardware_concurrency() << " concurrent threads supported.";
	LOG("main", loglev::INFO) << "OpenGL Version: " << glGetString(GL_VERSION);
	LOG("main", loglev::INFO) << "GLEW Version:   " << glewGetString(GLEW_VERSION);
	
	// ---- Create all systems, and add them to the core vector
	try {
		core->add_sys(engine::SYSid::input, new engine::sys_input);
		
		core->add_sys(engine::SYSid::gui, new engine::sys_gui(win));
		SYS_SUBSCRIBE(engine::SYSid::gui, 
			engine::ev_channel::INPUT_MOUSE_BTN | engine::ev_channel::INPUT_CHAR | engine::ev_channel::INPUT_WIN_SIZE
			| engine::ev_channel::INPUT_CURSOR_POS | engine::ev_channel::EXIT | engine::ev_channel::INPUT_KEY
		);
		gui = core->get_sys<engine::sys_gui>(engine::SYSid::gui);
		
		core->add_sys(engine::SYSid::gstate, new engine::sys_gstate);
		SYS_SUBSCRIBE(engine::SYSid::gstate,
			engine::ev_channel::INPUT_MOUSE_BTN | engine::ev_channel::INPUT_CHAR | engine::ev_channel::INPUT_WIN_SIZE
			| engine::ev_channel::INPUT_CURSOR_POS | engine::ev_channel::EXIT | engine::ev_channel::INPUT_KEY
		);
		gstate = core->get_sys<engine::sys_gstate>(engine::SYSid::gstate);
		
	} catch(std::runtime_error& ex) {
		LOG("main", loglev::FATAL) << "Exception at 'engine::system' creation: '" << ex.what() << "'.";
		EXIT_EXCEPT(-1);
	}
	
	// Attach input callbacks to input functions that will generate event messages
	engine::sys_input_attach(win);
	
	// ---- Quaid, start the reactor!
	core->bootstrap();
	
	// Create game states
	auto main_screen = gstate->add_state(new game::main_screen(gui->new_layout()));
	gstate->set_active_state(main_screen);
	
	boost::filesystem::path p(p_core);
	std::time_t lmod, diff, lcheck = std::time(0);
	
	float r, g, b;
	r = int(bg_ct["r"]) / 255.f;
	g = int(bg_ct["g"]) / 255.f;
	b = int(bg_ct["b"]) / 255.f;
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glEnable(GL_TEXTURE_2D);
	
	// ---- CONTROL THE MAIN LOOP RIGHT HERE (somehow)
	ftime = nftime = time = ntime = glfwGetTime();
	while(!core->m_should_close) {
		ftime = nftime;
	
		// --- render
		glClearColor(r, g, b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		gstate->draw();
		
		glfwSwapBuffers(win);
		
		// --- handle events
		glfwPollEvents();
		
		// --- update
		core->update_all(0.5f);
		
		gstate->update(0.5f);
		
		// --- end of loop
		ntime = nftime = glfwGetTime();
		if((ntime - time) > 2) {
			time = ntime;
			LOG("main", loglev::INFO) << "FPS: " << int(1 / (nftime - ftime));
			
			if(boost::filesystem::exists(p)) {
				lmod = boost::filesystem::last_write_time(p);
				diff = lcheck - lmod;
				lcheck = std::time(NULL);
				if(diff <= 0) {
					// file has been modified since last check - reload it
				}
			}
		}
	}
	
	core->shut_down();
}

int main(int argc, char** argv)
{
#ifdef OS_LINUX
	// no root - thank you 0A.D - https://github.com/0ad/0ad/blob/master/source/main.cpp
	if (geteuid() == 0)
	{
		std::cerr << "********************************************************\n"
				  << "WARNING: Attempted to run the game with root permission!\n"
				  << "This is not allowed because it can alter home directory \n"
				  << "permissions and opens your system to vulnerabilities.   \n"
				  << "(You received this message because you were either      \n"
				  <<"  logged in as root or used e.g. the 'sudo' command.) \n"
				  << "********************************************************\n";
		return EXIT_FAILURE;
	}
#endif // OS_LINUX

	core = std::unique_ptr<engine::core>(new engine::core(std::vector<std::string>(argv, argv+argc)));
	
	try {
		run();
		
	} catch(engine::exit_exception& e) {
		LOG("main", loglev::INFO) << "Catched exit_exception!";
		TERMINATE(e.c);
	}

	LOG("main", loglev::INFO) << "Closing down.";
	TERMINATE(EXIT_SUCCESS);
}
