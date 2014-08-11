#include "engine/event_manager.hpp"

using namespace engine;

event_manager::event_manager()
{
	LOG("INFO", "Event manager created.");
}
event_manager::~event_manager()
{
	LOG("INFO", "Event manager dying.");
}

void event_manager::subscribe(subscription sub)
{
	m_subs.push_back(sub);
}

void event_manager::broadcast(event_t event)
{
	for(auto it = m_subs.begin(); it != m_subs.end(); it++) {
		if(it->m_channels & event.m_channel) {
			it->m_sys->handle_event(event);
		}
	}
}

