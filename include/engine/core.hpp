#pragma once

#include <engine/globals.hpp>

#include <vector>

namespace engine {

class core {
	
	// This is the map of the universe, my friend.
	std::map<uint, std::unique_ptr<system>> systems;
	
public:

	void add_sys(SYSid sid, std::unique_ptr<system> sys);

};

}
