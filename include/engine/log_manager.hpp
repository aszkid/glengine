#pragma once

#include <memory>
#include <string>
#include <sstream>
#include "globals.hpp"

namespace engine {

	// base logger class - inherit from this one (i guess)
	class logger {
		std::stringstream buff;
	public:
		// copy constructors, to avoid sstream hell
		logger(const logger &l);
		logger& operator=(const logger &l);
	
		logger();
		~logger();
		
		template<typename T>
		logger& operator <<(const T& val)
		{
			buff << val;
			return *this;
		}
	};

	// logger_manager -> holds vector<log_cfg> 
	// log_mngr->get("logger") || returns a new logger that has a pointer to its parent (log_cfg).
	// when the logger dies, it dispatches to its parent the str() of the stringstream.

	class log_manager {
	public:
		log_manager();
		~log_manager();
		
		logger get();
	};
	
	typedef std::unique_ptr<log_manager> log_manager_ptr;
	extern log_manager_ptr log_mngr;
	#define LOG_DECL() engine::log_manager_ptr engine::log_mngr;

}
