#include "main_screen.hpp"

using namespace game;

main_screen::main_screen(gui::layout *layout)
	: gstate::state(layout)
{
	m_cfg = &cfg_mngr->get("../../../rundir/cfg/states/main_screen.lua");
	
	const float spacing = 20.f;
	const float topmar = 30.f;
	std::array<engine::gui::component::button*, 3> btns;
	
	btns[0] = m_layout->new_component<engine::gui::component::button>(
		"PLAY", glm::vec2(topmar, topmar), 10, glm::vec2(300, -1)
	);
	btns[1] = m_layout->new_component<engine::gui::component::button>(
		"OPTIONS", glm::vec2(topmar, (btns[0]->m_size.y + btns[0]->m_pos.y) + spacing), 10, glm::vec2(300, -1)
	);
	btns[2] = m_layout->new_component<engine::gui::component::button>(
		"EXIT", glm::vec2(topmar, (btns[1]->m_size.y + btns[1]->m_pos.y) + spacing), 10, glm::vec2(300, -1)
	);
	
	auto title = m_layout->new_component<engine::gui::component::label>(
		"OPENMILSIM", 100
	);
	title->set_font("bebas-neue/BebasNeue.otf");
	glm::vec2 tbbox = title->m_bbox;
	title->set_pos(glm::vec2(
		m_layout->m_viewport->x - tbbox.x - 10,
		m_layout->m_viewport->y - tbbox.y - 10
	));
	title->set_col(glm::vec4(.1, .1, .1, .7));
	
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
void main_screen::handle_event(event_t *event)
{}
