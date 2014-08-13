#include "engine/event_manager.hpp"

using namespace engine;

event_manager::event_manager()
{}
event_manager::~event_manager()
{}

void event_manager::subscribe(subscription sub)
{
	m_subs.push_back(sub);
}

void event_manager::broadcast(event_t *event)
{
	std::unique_ptr<event_t> ev_ptr(event);
	
	for(auto it = m_subs.begin(); it != m_subs.end(); it++) {
		if(it->m_channels & ev_ptr->m_channel) {
			it->m_sys->handle_event(ev_ptr.get());
		}
	}
}

