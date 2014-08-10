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
		throw std::runtime_error(MKSTR("System with ID " << sid << " is already in the systems vector!"));
	}
	
	m_systems[sid] = sys;
}
sys_ptr core::get_sys(SYSid sid)
{
	if(!sys_exists(sid)) {
		throw std::runtime_error(MKSTR("System with ID " << sid << " does not exist, cannot retrieve!"));
	}
	
	return m_systems[sid];
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

