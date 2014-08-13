#pragma once

#include <stdexcept>
#include <memory>

#include "engine/event.hpp"

namespace engine {

	class system {

	public:
		system();
		virtual ~system();

		virtual void init();
		virtual void shut_down();
		virtual void update(float dt);
		virtual void handle_event(event_t event);

	};
	
	typedef std::unique_ptr<system> sys_ptr;

}
