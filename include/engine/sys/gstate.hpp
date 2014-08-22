#pragma once

#include "gstate/state.hpp"

#include "engine/globals.hpp"
#include "engine/system.hpp"
#include "engine/event_manager.hpp"


namespace engine {

	class sys_gstate : public system {
		
	
	public:
		sys_gstate();
		~sys_gstate();

		void init();
		void shut_down();
		void update(float dt);
		
	};

}
