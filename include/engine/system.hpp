#pragma once

#include <stdexcept>
#include <memory>

#include "engine/event.hpp"

namespace engine {

	class system {

	public:
		system();
		virtual ~system();

		virtual void init() = 0;
		virtual void shut_down() = 0;
		virtual void update(float dt) = 0;
		virtual void handle_event(event_t *event) = 0;

	};
	
	typedef std::unique_ptr<system> sys_ptr;

}
