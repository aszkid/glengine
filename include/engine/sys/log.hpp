#pragma once

#include "engine/globals.hpp"
#include "engine/system.hpp"

namespace engine {
	
	class sys_log : public system {

	public:
	
		sys_log();
		~sys_log();
	
		void init();
		void shut_down();
		void update(float dt);

	};
	
}
