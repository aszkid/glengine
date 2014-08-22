#pragma once

#include <GLFW/glfw3.h>

#include "engine/globals.hpp"
#include "engine/system.hpp"
#include "engine/event.hpp"

#include <map>
#include <vector>
#include <memory>
#include <type_traits>

namespace engine {

	class core {
	
		// This is the map of the universe, my friend.
		std::map<SYSid, sys_ptr> m_systems;
		std::vector<std::string> m_args;
	
	public:
		bool m_should_close;
		
		core(std::vector<std::string> args);
		~core();

		void add_sys(SYSid sid, system *sys);
		system* get_sys(SYSid sid);
		
		template<class T>
		typename std::enable_if<std::is_base_of<system, T>::value, T*>::type
		get_sys(SYSid sid)
		{
			return static_cast<T*>(get_sys(sid));
		}
		
		bool sys_exists(SYSid sid);
		
		void update_all(float dt);
		
		void handle_event(event_t *ev);
		
		void bootstrap();
		void shut_down();

	};

}
