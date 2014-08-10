#pragma once

#include <stdexcept>
#include <memory>

namespace engine {

	class system {

	public:
		system();
		virtual ~system();

		virtual void init();
		virtual void shut_down();
		virtual void update(float dt);

	};
	
	typedef std::shared_ptr<system> sys_ptr;

}
