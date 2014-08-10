#include "engine/sys/log.hpp"

using namespace engine;

sys_log::sys_log()
{}
sys_log::~sys_log()
{}

void sys_log::init()
{
	LOG("INFO", "Successful engine::sys_log bootstrap.");
}
void sys_log::shut_down()
{
	LOG("INFO", "Successful engine::sys_log shut down.");
}

void sys_log::update(float dt)
{}

