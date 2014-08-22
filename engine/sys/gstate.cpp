#include "engine/sys/gstate.hpp"

using namespace engine;

sys_gstate::sys_gstate()
	: m_active_state(nullptr)
{}
sys_gstate::~sys_gstate()
{
	shut_down();
}

void sys_gstate::init()
{}
void sys_gstate::shut_down()
{
	{
		CHECK_ACTIVE_STATE;
		m_active_state->stop();
	}
}
void sys_gstate::update(float dt)
{
	CHECK_ACTIVE_STATE;
	
	m_active_state->update(dt);
}
void sys_gstate::draw()
{
	CHECK_ACTIVE_STATE;
	
	m_active_state->draw();
}

void sys_gstate::add_state(gstate::state *state)
{
	m_states.emplace_back(state);
}
