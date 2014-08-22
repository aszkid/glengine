#pragma once

#include <memory>
#include <string>
#include <map>
#include <stdexcept>

#include <sol.hpp>

#include "log_manager.hpp"

namespace engine {

	class config_manager {
	private:
		std::map<std::string, std::unique_ptr<sol::state>> m_files;
	
	public:
		config_manager();
		~config_manager();
	
		sol::state& get(const char *file);
	};
	
	typedef std::unique_ptr<config_manager> config_manager_ptr;
	extern config_manager_ptr cfg_mngr;
	#define CFG_DECL() engine::config_manager_ptr engine::cfg_mngr
}
