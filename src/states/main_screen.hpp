#pragma once

#include <engine/globals.hpp>

#include <engine/sys/gstate/state.hpp>
#include <engine/sys/gui/components/all.hpp>

namespace game {

	using namespace engine;
	
	class main_screen : public gstate::state {
	private:
		lua::State* m_cfg;
	public:
		main_screen(gui::layout *layout);
		~main_screen();
		
		void stop();
		void update(float dt);
		void draw();
		gstate::state* is_over();
	};

}
