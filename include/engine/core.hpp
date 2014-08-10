#pragma once

#include "engine/globals.hpp"
#include "engine/system.hpp"

#include <map>
#include <vector>
#include <memory>

namespace engine {

	class core {
	
		// This is the map of the universe, my friend.
		std::map<uint, std::unique_ptr<system>> mSystems;
		std::vector<std::string> mArgs;
	
	public:
		core(std::vector<std::string> args);
		~core();

		void add_sys(SYSid sid, std::unique_ptr<system> sys);
		
		void bootstrap();
		void shut_down();

	};

}
