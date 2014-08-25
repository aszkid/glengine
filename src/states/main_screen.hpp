#pragma once

#include <engine/globals.hpp>

#include <engine/sys/gstate/state.hpp>
#include <engine/sys/gui/components/all.hpp>

#include <engine/sys/gui/api/rectangle.hpp>

namespace game {

	using namespace engine;
	
	class main_screen : public gstate::state {
	private:
		sol::state* m_cfg;
		
		void goto_play();
		void goto_exit();
		void goto_opts();
		
		gui::api::rectangle rect;
	public:
		main_screen(gui::layout *layout);
		~main_screen();
		
		void stop();
		void update(float dt);
		void draw();
		void handle_event(event_t *event);
		gstate::state* is_over();
	};

}
