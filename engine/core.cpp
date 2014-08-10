#include "engine/core.hpp"

using namespace engine;

core::core(std::vector<std::string> args)
	: mArgs(args)
{
}

core::~core()
{

}

void core::add_sys(SYSid sid, std::unique_ptr<system> sys)
{
	if(mSystems.find(sid) != mSystems.end()) {
		throw std::runtime_error(MKSTR("System with ID " << sid << " is already in the systems vector!"));
	}
	
	mSystems[sid] = std::move(sys);
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
