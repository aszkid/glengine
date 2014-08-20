#pragma once

#include <GLFW/glfw3.h>

#include "engine/globals.hpp"
#include "engine/system.hpp"
#include "engine/event.hpp"

#include <map>
#include <vector>
#include <memory>

namespace engine {

	class core {
	
		// This is the map of the universe, my friend.
		std::map<SYSid, sys_ptr> m_systems;
		std::vector<std::string> m_args;
	
	public:
		bool m_should_close;
		
		core(std::vector<std::string> args);
		~core();

		void add_sys(SYSid sid, sys_ptr sys);
		system* get_sys(SYSid sid);
		bool sys_exists(SYSid sid);
		
		void update_all(float dt);
		
		void route_event(event_t *ev, system *sys);
		
		void bootstrap();
		void shut_down();

	};

}
