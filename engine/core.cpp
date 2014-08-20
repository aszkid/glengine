#include "engine/core.hpp"

using namespace engine;

core::core(std::vector<std::string> args)
	: m_args(args), m_should_close(false)
{}

core::~core()
{
	shut_down();
}

bool core::sys_exists(SYSid sid)
{
	return (m_systems.find(sid) != m_systems.end());
}

void core::add_sys(SYSid sid, sys_ptr sys)
{
	if(sys_exists(sid)) {
		throw std::runtime_error(MKSTR("System with ID " << uint(sid) << " is already in the systems vector!"));
	}
	
	m_systems[sid] = std::move(sys);
}
engine::system* core::get_sys(SYSid sid)
{
	if(!sys_exists(sid)) {
		throw std::runtime_error(MKSTR("System with ID " << uint(sid) << " does not exist, cannot retrieve!"));
	}
	
	return m_systems[sid].get();
}

void core::update_all(float dt)
{
	for(auto it = m_systems.begin(); it != m_systems.end(); it++) {
		it->second->update(dt);
	}
}
void core::route_event(event_t *ev, system *sys)
{
	if(ev->m_channel == EXIT) {
		m_should_close = true;
	} else if(ev->m_channel == INPUT_KEY) {
		auto _ev = static_cast<events::input_key*>(ev);
		if(_ev->m_key == GLFW_KEY_ESCAPE) {
			switch(_ev->m_action) {
			case GLFW_PRESS:
				m_should_close = true;
				break;
			}
		}
	}
	sys->handle_event(ev);
}


void core::bootstrap()
{
	for(auto it = m_systems.begin(); it != m_systems.end(); it++) {
		it->second->init();
	}
}
void core::shut_down()
{
	for(auto it = m_systems.begin(); it != m_systems.end(); it++) {
		if(!it->second)
			continue;
		it->second->shut_down();
		it->second.reset();
	}
}

