#include "main_screen.hpp"

using namespace game;

main_screen::main_screen(gui::layout *layout)
	: gstate::state(layout)
{
	m_cfg = &cfg_mngr->get("../../../rundir/cfg/states/main_screen.lua");

	m_layout->new_component<engine::gui::component::label>(
		engine::cstr_to_wstr(m_cfg->get<const char*>("hello")).c_str(), 50);
	m_layout->new_component<engine::gui::component::label>(
		engine::cstr_to_wstr(m_cfg->get<const char*>("world")).c_str(), 120, glm::vec2(50, 50), glm::vec4(0.1, 0.1, 0.1, 1), "bebas-neue/BebasNeue.otf");
	m_layout->new_component<engine::gui::component::label>(
		engine::cstr_to_wstr(m_cfg->get<const char*>("foobar")).c_str(), 35, glm::vec2(50, 160), glm::vec4(0.1, 0.1, 0.1, 1), "fira-sans/FiraSans-LightItalic.otf");
	
}
main_screen::~main_screen()
{}

void main_screen::stop()
{}
void main_screen::update(float dt)
{}
void main_screen::draw()
{
	
	m_layout->draw();

}
gstate::state* main_screen::is_over()
{
	return nullptr;
}
