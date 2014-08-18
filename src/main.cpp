#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <thread>
#include <typeinfo>
#include <csignal>

#include <engine/globals.hpp>
#include <engine/event_manager.hpp>
#include <engine/config_manager.hpp>
#include <engine/log_manager.hpp>
#include <engine/core.hpp>

#include <engine/sys/input.hpp>
#include <engine/sys/gui.hpp>

#include <engine/tools/shader.hpp>

#define SYS_MKPTR(s) engine::sys_ptr(new s)
#define SYS_SUBSCRIBE(s, ch) engine::ev_mngr->subscribe(engine::subscription(ch, core.get_sys(s)));

// CHECK THIS OUT M8: https://gcc.gnu.org/onlinedocs/gcc/Variadic-Macros.html
#define GUI_NEW_COMPONENT(type, layout, ...) dynamic_cast<type*>(layout->add_component(new type(layout, ## __VA_ARGS__)))


struct exit_exception { 
   int c; 
   exit_exception(int c):c(c) { } 
};


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


void cleanup(engine::core& c)
{
	c.shut_down();
	glfwTerminate();
}
#define EXCEPT(c) throw exit_exception(c);
#define TERMINATE(val) cleanup(core); return val;

void signal_handler(int code)
{
	LOG("main", loglev::INFO) << "Received signal '" << code << "'.";
	EXCEPT(code);
}

EV_DECL();
CFG_DECL();
LOG_DECL();

void run(int argc, char** argv, engine::core& core)
{
	std::map<int,int> hints;
	GLFWwindow *win;
	GLenum err;
	double ftime, nftime, time, ntime;
	
	std::setlocale(LC_CTYPE, "");
	
	// Initialize the log manager
	engine::log_mngr = engine::log_manager_ptr(new engine::log_manager());
	// Initialize the config manager
	engine::cfg_mngr = engine::config_manager_ptr(new engine::config_manager());
	// Initialize the event manager
	engine::ev_mngr = engine::event_manager_ptr(new engine::event_manager());
	
	// -----
	// premake all the loggers
	using engine::log_mngr;
	log_mngr->make<engine::void_logger>("void");
	log_mngr->make("main");
	log_mngr->make("ev_mngr");
	log_mngr->make("cfg_mngr");
	log_mngr->make("sys_gui");
	log_mngr->make("core");
	log_mngr->make("t_shader");
	// -----
	
	// set up signal handler
	/*std::signal(SIGTERM, signal_handler);
	std::signal(SIGABRT, signal_handler);
	std::signal(SIGINT, signal_handler);*/

	std::signal(SIGTERM, [](int){
		EXCEPT(0);
	});
	std::signal(SIGABRT, [](int){
		EXCEPT(0);
	});
	std::signal(SIGINT, [](int){
		EXCEPT(0);
	});
	
	// preload our config files
	auto& base_cfg = engine::cfg_mngr->get("../../../rundir/cfg/core.lua");
	auto& gui_cfg = engine::cfg_mngr->get("../../../rundir/cfg/gui.lua");
	
	// ---- Initialize window and GL context
	glfwSetErrorCallback(glfw_err_callback);
	if(!glfwInit()) {
		LOG("main", loglev::FATAL) << "Could not initialize GLFW!";
		EXCEPT(-1);
	}
	
	// Prepare a pointer to the GUI system, we want to access it directly to build a test UI
	engine::sys_gui* gui;
	
	float gl_v = float(base_cfg["gl_v"]["major"]) + float(base_cfg["gl_v"]["minor"]) / 10.0f;
	if(gl_v < 3.2f) {
		LOG("main", loglev::FATAL) << "OpenGL version provided (" << gl_v << ") is not supported! OpenGL >=3.2 required.";
		EXCEPT(-1);
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
		LOG("main", loglev::FATAL) << "Could not create window!";
		EXCEPT(-1);
	}
	
	glGetError();
	// Initialize GLEW, and thus load GL function pointers
	err = glewInit();
	if(GLEW_OK != err) {
		LOG("main", loglev::FATAL) << "GLEW_ERR: '" << glewGetErrorString(err) << "'.";
		EXCEPT(-1);
	}
	
	LOG("main", loglev::INFO) << std::thread::hardware_concurrency() << " concurrent threads supported.";
	LOG("main", loglev::INFO) << "OpenGL Version: " << glGetString(GL_VERSION);
	LOG("main", loglev::INFO) << "GLEW Version:   " << glewGetString(GLEW_VERSION);
	
	// ---- Create all systems, and add them to the core vector
	try {
		core.add_sys(engine::SYSid::input, SYS_MKPTR(engine::sys_input));
		
		core.add_sys(engine::SYSid::gui, SYS_MKPTR(engine::sys_gui(win)));
		SYS_SUBSCRIBE(engine::SYSid::gui, 
			engine::ev_channel::INPUT_MOUSE_BTN | engine::ev_channel::INPUT_CHAR | engine::ev_channel::INPUT_WIN_SIZE
			| engine::ev_channel::INPUT_CURSOR_POS
		);
		gui = dynamic_cast<engine::sys_gui*>(core.get_sys(engine::SYSid::gui));
		
		
	} catch(std::runtime_error& ex) {
		LOG("main", loglev::FATAL) << "Exception at 'engine::system' creation: '" << ex.what() << "'.";
		EXCEPT(-1);
	}
	
	// Attach input callbacks to input functions that will generate event messages
	engine::sys_input_attach(win);
	
	// ---- Quaid, start the reactor!
	core.bootstrap();
	
	
	// Load GUI layouts (future: on demand, script based?)
	auto layout = gui->new_layout();
	GUI_NEW_COMPONENT(engine::gui::component::label,
		layout, engine::cstr_to_wstr(gui_cfg["txt"]["title"]).c_str(), 120, glm::vec2(50, 50), "bebas-neue/BebasNeue.otf");
	GUI_NEW_COMPONENT(engine::gui::component::label,
		layout, engine::cstr_to_wstr(gui_cfg["txt"]["line"]).c_str(), 50);
	GUI_NEW_COMPONENT(engine::gui::component::label,
		layout, engine::cstr_to_wstr(gui_cfg["txt"]["subtitle"]).c_str(), 35, glm::vec2(50, 160), "fira-sans/FiraSans-LightItalic.otf");
	GUI_NEW_COMPONENT(engine::gui::component::button, layout, glm::vec2(500));
	//GUI_NEW_COMPONENT(engine::gui::component::window, layout);
	
	
	// ----------
	
	float r, g, b;
	r = float(base_cfg["bg_c"]["r"]) / 255.f;
	g = float(base_cfg["bg_c"]["g"]) / 255.f;
	b = float(base_cfg["bg_c"]["b"]) / 255.f;
	
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
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
			LOG("main", loglev::INFO) << "FPS: " << int(1 / (nftime - ftime));
		}
	}
}

int main(int argc, char** argv)
{
	engine::core core(std::vector<std::string>(argv, argv+argc));
	
	try {
		run(argc, argv, core);
		
	} catch(exit_exception& e) {
		LOG("main", loglev::INFO) << "Catched exit_exception!";
		TERMINATE(e.c);
	}

	LOG("main", loglev::INFO) << "Closing down.";
	TERMINATE(EXIT_SUCCESS);
}
