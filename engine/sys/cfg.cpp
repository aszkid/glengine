#include "engine/sys/cfg.hpp"

using namespace engine;

sys_cfg::sys_cfg()
{}
sys_cfg::~sys_cfg()
{}

void sys_cfg::init()
{
	LOG("INFO", "Successful engine::sys_cfg bootstrap.");
}
void sys_cfg::shut_down()
{
	LOG("INFO", "Successful engine::sys_cfg shut down.");
}

void sys_cfg::update(float dt)
{}

