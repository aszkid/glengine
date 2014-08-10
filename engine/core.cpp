#include "engine/core.hpp"

using namespace engine;

core::core(std::vector<std::string> args)
	: mArgs(args)
{
}

core::~core()
{

}

bool core::sys_exists(SYSid sid)
{
	return (mSystems.find(sid) != mSystems.end());
}

void core::add_sys(SYSid sid, sys_ptr sys)
{
	if(sys_exists(sid)) {
		throw std::runtime_error(MKSTR("System with ID " << sid << " is already in the systems vector!"));
	}
	
	mSystems[sid] = sys;
}
sys_ptr core::get_sys(SYSid sid)
{
	if(!sys_exists(sid)) {
		throw std::runtime_error(MKSTR("System with ID " << sid << " does not exist, cannot retrieve!"));
	}
	
	return mSystems[sid];
}


void core::bootstrap()
{
	for(auto it = mSystems.begin(); it != mSystems.end(); it++) {
		it->second->init();
	}
}
void core::shut_down()
{
	for(auto it = mSystems.begin(); it != mSystems.end(); it++) {
		it->second->shut_down();
	}
}

