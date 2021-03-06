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

gstate::state* sys_gstate::add_state(const std::string name, gstate::state *state)
{
	m_states[name] = gstate::state_ptr(state);
	return m_states[name].get();
}
void sys_gstate::set_active_state(gstate::state *state)
{
	if(m_active_state)
		m_active_state->stop();
	m_active_state = state;
}
void sys_gstate::set_active_state(const std::string state)
{
	if(m_active_state)
		m_active_state->stop();
	m_active_state = m_states[state].get();
}
void sys_gstate::handle_event(event_t *event)
{
	if(event->m_channel == ev_channel::STATE_CHANGE) {
		auto _ev = static_cast<events::state_change*>(event);
		if(m_states.find(_ev->m_to) != m_states.end())
			set_active_state(_ev->m_to);
		else
			LOG("sys_gstate", log::INFO) << "Sorry son, that state does not exist.";
	}

	if(!m_active_state)
		return;
	m_active_state->handle_event(event);
}
