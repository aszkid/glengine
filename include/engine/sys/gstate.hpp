#pragma once

#include "gstate/state.hpp"

#include "engine/globals.hpp"
#include "engine/system.hpp"
#include "engine/event_manager.hpp"

#include <vector>
#include <map>

namespace engine {

	class sys_gstate : public system {
		std::map<std::string, gstate::state_ptr> m_states;
		gstate::state *m_active_state;
	
	public:
		sys_gstate();
		~sys_gstate();
		
		gstate::state* add_state(const std::string name, gstate::state *state);
		void set_active_state(gstate::state *state);
		void set_active_state(const std::string state);

		void init();
		void shut_down();
		void update(float dt);
		void draw();
		void handle_event(event_t *event);
		
	};

}
