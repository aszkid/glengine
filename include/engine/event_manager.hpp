#pragma once

#include "engine/event.hpp"
#include "engine/system.hpp"

namespace engine {

	struct subscription {
		subscription() {}
		subscription(uint channels, sys_ptr sys) : m_channels(channels), m_sys(sys) {}
	
		uint m_channels; // channel mask
		sys_ptr m_sys;
	};
	
	class event_manager {

	public:
		event_manager();
		~event_manager();
		
		// subscribe a system
		void subscribe(subscription sub);
		// broadcast an event to the concerned systems
		void broadcast(event_t event);
		
	private:
		// list of subscribers
		std::vector<subscription> m_subs;
	};
	
}
