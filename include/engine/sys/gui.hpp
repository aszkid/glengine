#pragma once

#include <GL/glew.h>

#include <vector>
#include <memory>

#include "engine/system.hpp"
#include "gui/layout.hpp"

#include "gui/components/button.hpp"

namespace engine {

	class sys_gui : public system {
	
	private:
		typedef std::vector<std::unique_ptr<gui::layout>> layout_list;
		typedef gui::layout* layout_handle;
		
		layout_list m_layouts;
		layout_handle m_active_layout;
		
	public:
		sys_gui();
		~sys_gui();

		void init();
		void shut_down();
		void update(float dt);
		void handle_event(event_t event);
		void draw();
		
		layout_handle new_layout();
	};

}
