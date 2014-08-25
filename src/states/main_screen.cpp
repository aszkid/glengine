#include "main_screen.hpp"

using namespace game;

main_screen::main_screen(gui::layout *layout)
	: gstate::state(layout), rect(layout->m_viewprojmat, glm::vec2(100), glm::vec2(20), glm::vec4(1, 0, 0, 1))
{
	m_cfg = &cfg_mngr->get("../../../rundir/cfg/states/main_screen.lua");
	
	
	
	
	const float spacing = 20.f;
	const float topmar = 50.f;
	std::array<engine::gui::component::button*, 3> btns;
	
	auto img = m_layout->new_component<engine::gui::component::image>(
		"real.jpg", glm::vec2(0), *m_layout->m_viewport
	);
	
	btns[0] = m_layout->new_component<engine::gui::component::button>(
		"PLAY", glm::vec2(topmar, topmar), 10, glm::vec2(300, -1)
	);
	btns[1] = m_layout->new_component<engine::gui::component::button>(
		"OPTIONS", glm::vec2(topmar, (btns[0]->m_size.y + btns[0]->m_pos.y) + spacing), 10, glm::vec2(300, -1)
	);
	btns[2] = m_layout->new_component<engine::gui::component::button>(
		"EXIT", glm::vec2(topmar, (btns[1]->m_size.y + btns[1]->m_pos.y) + spacing), 10, glm::vec2(300, -1)
	);
	
	// bind function callbacks
	btns[0]->add_callback_fun("lclick", std::bind(&main_screen::goto_play, this));
	btns[1]->add_callback_fun("lclick", std::bind(&main_screen::goto_opts, this));
	btns[2]->add_callback_fun("lclick", std::bind(&main_screen::goto_exit, this));
	
	auto vers = m_layout->new_component<engine::gui::component::label>(
		"DEV", 35
	)->set_font("bebas-neue/BebasNeue.otf")->set_col(glm::vec4(.9, .9, .9, .5));
	glm::vec2 vbbox = vers->m_bbox;
	
	auto title = m_layout->new_component<engine::gui::component::label>(
		"OPENMILSIM", 50
	)->set_font("bebas-neue/BebasNeue.otf")->set_col(glm::vec4(.9, .9, .9, .5));
	glm::vec2 tbbox = title->m_bbox;
	title->set_pos(glm::vec2(
		m_layout->m_viewport->x - tbbox.x - 15 - vbbox.x,
		m_layout->m_viewport->y - tbbox.y - 10
	));
	
	vers->set_pos(glm::vec2(
		m_layout->m_viewport->x - vbbox.x - 10,
		title->m_pos.y + tbbox.y - vbbox.y
	));
}
main_screen::~main_screen()
{}

void main_screen::stop()
{}
void main_screen::update(float dt)
{
	m_layout->update();
}
void main_screen::draw()
{
	
	
	m_layout->draw();
	rect.draw();

}
gstate::state* main_screen::is_over()
{
	return nullptr;
}
void main_screen::handle_event(event_t *event)
{
	m_layout->handle_event(event);
}
void main_screen::goto_play()
{
	LOG("state", log::INFO) << "Going to PLAY!";
	engine::ev_mngr->broadcast(new engine::events::state_change(engine::ev_channel::STATE_CHANGE, "play"));
	rect.set_position(rect.m_pos + glm::vec2(2));
}
void main_screen::goto_exit()
{
	engine::ev_mngr->broadcast(new engine::events::exit(engine::ev_channel::EXIT, 0));
}
void main_screen::goto_opts()
{
	rect.set_color(rect.m_color + glm::vec4(0, 0, 0, -0.075));
}
