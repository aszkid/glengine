#include "main_screen.hpp"

using namespace game;

main_screen::main_screen(gui::layout *layout)
	: gstate::state(layout)
{
	m_cfg = &cfg_mngr->get("../../../rundir/cfg/states/main_screen.lua");

	m_layout->new_component<engine::gui::component::label>(
		m_cfg->get<std::string>("hello"), 50
	);
	m_layout->new_component<engine::gui::component::label>(
		m_cfg->get<std::string>("world"), 120, glm::vec2(50, 50), glm::vec4(0.1, 0.1, 0.1, 1), "bebas-neue/BebasNeue.otf"
	);
	m_layout->new_component<engine::gui::component::label>(
		m_cfg->get<std::string>("foobar"), 35, glm::vec2(50, 160), glm::vec4(0.1, 0.1, 0.1, 1), "fira-sans/FiraSans-LightItalic.otf"
	);
	
	m_layout->new_component<engine::gui::component::button>(
		"PLAY"
	);
	
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
