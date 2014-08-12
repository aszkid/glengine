#pragma once

#include "engine/globals.hpp"
#include "engine/system.hpp"

#include <map>
#include <vector>
#include <memory>

namespace engine {

	class core {
	
		// This is the map of the universe, my friend.
		std::map<SYSid, sys_ptr> m_systems;
		std::vector<std::string> m_args;
	
	public:
		core(std::vector<std::string> args);
		~core();

		void add_sys(SYSid sid, sys_ptr sys);
		sys_ptr get_sys(SYSid sid);
		system* get_sys_raw(SYSid sid);
		bool sys_exists(SYSid sid);
		
		void update_all(float dt);
		
		void bootstrap();
		void shut_down();

	};

}
