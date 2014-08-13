#include "engine/core.hpp"

using namespace engine;

core::core(std::vector<std::string> args)
	: m_args(args)
{
}

core::~core()
{

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


void core::bootstrap()
{
	for(auto it = m_systems.begin(); it != m_systems.end(); it++) {
		it->second->init();
	}
}
void core::shut_down()
{
	for(auto it = m_systems.begin(); it != m_systems.end(); it++) {
		it->second->shut_down();
	}
}

