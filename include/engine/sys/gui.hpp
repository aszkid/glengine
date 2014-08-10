#pragma once

#include "engine/system.hpp"

namespace engine {

	class sys_gui : public system {
	
	public:
		sys_gui();
		~sys_gui();

		void init();
		void shut_down();
		void update(float dt);
	};

}
