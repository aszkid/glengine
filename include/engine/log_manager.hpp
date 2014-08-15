#pragma once

#include <memory>
#include <string>
#include <sstream>
#include <map>
#include "globals.hpp"

namespace engine {

	// base logger class - inherit from this one (i guess)
	class logger {
		std::string m_name;
	public:
		logger(const std::string &name);
		virtual ~logger();
		
		virtual void handle(const std::string& val);
	};
	
	// logger instance
	class log_instance {
		std::stringstream m_buff;
		logger *m_parent;
	public:
		// copy constructors, to avoid sstream hell
		log_instance(const log_instance &l);
		log_instance& operator=(const log_instance &l);
	
		log_instance(logger *parent);
		~log_instance();
		
		template<typename T>
		log_instance& operator <<(const T& val)
		{
			m_buff << val;
			return *this;
		}
	};

	// logger_manager -> holds vector<log_cfg> 
	// log_mngr->get("logger") || returns a new logger that has a pointer to its parent (log_cfg).
	// when the logger dies, it dispatches to its parent the str() of the stringstream.

	class log_manager {
		std::map<std::string, std::unique_ptr<logger>> m_loggers;
	public:
		log_manager();
		~log_manager();
		
		void make(const std::string &name);
		log_instance get(const std::string &name);
	};
	
	typedef std::unique_ptr<log_manager> log_manager_ptr;
	extern log_manager_ptr log_mngr;
	#define LOG_DECL() engine::log_manager_ptr engine::log_mngr;

}
