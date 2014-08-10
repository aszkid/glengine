#pragma once

#include "engine/globals.hpp"
#include "engine/system.hpp"

namespace engine {
	
	class sys_cfg : public system {

	public:
	
		sys_cfg();
		~sys_cfg();
	
		void init();
		void shut_down();
		void update(float dt);

	};
	
}
