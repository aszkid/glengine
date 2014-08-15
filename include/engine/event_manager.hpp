#pragma once

#include <memory>

#include "engine/event.hpp"
#include "engine/globals.hpp"
#include "engine/system.hpp"

namespace engine {

	struct subscription {
		subscription() {}
		subscription(uint channels, system* sys) : m_channels(channels), m_sys(sys) {}
	
		uint m_channels; // channel mask
		system* m_sys;
	};
	
	class event_manager {

	public:
		event_manager();
		~event_manager();
		
		// subscribe a system
		void subscribe(subscription sub);
		// broadcast an event to the concerned systems
		void broadcast(event_t *event);
		
	private:
		// list of subscribers
		std::vector<subscription> m_subs;
	};
	
	typedef std::unique_ptr<event_manager> event_manager_ptr;
	extern event_manager_ptr ev_mngr;
	#define EV_DECL() engine::event_manager_ptr engine::ev_mngr;
}
