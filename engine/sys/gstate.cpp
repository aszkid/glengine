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
	if(m_active_state)
		m_active_state->stop();
}
void sys_gstate::update(float dt)
{
	if(m_active_state)
		m_active_state->update(dt);
}
void sys_gstate::draw()
{
	if(!m_active_state)
		return;
	m_active_state->draw();
}

gstate::state* sys_gstate::add_state(gstate::state *state)
{
	m_states.emplace_back(state);
	return m_states.back().get();
}
void sys_gstate::set_active_state(gstate::state *state)
{
	if(m_active_state)
		m_active_state->stop();
	m_active_state = state;
}
