#pragma once

#include "engine/globals.hpp"
#include "engine/system.hpp"
#include "engine/event_manager.hpp"

namespace engine {

	class sys_state : public system {
	
	public:
		sys_state();
		~sys_state();

		void init();
		void shut_down();
		void update(float dt);
		
	};

}
