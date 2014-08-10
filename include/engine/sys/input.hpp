#pragma once

#include "engine/system.hpp"

namespace engine {

	class sys_input : public system {
	
	public:
		sys_input();
		~sys_input();

		void init();
		void shut_down();
		void update(float dt);
		
	};

}
