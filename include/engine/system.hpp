#pragma once

#include <stdexcept>

namespace engine {

	class sys_except : public std::runtime_error {
	public:
		sys_except();
	};

	class system {

	public:

		system();
		virtual ~system();

		virtual void init();
		virtual void shut_down();
		virtual void update(float dt);

	};

}
