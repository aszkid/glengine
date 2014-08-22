#pragma once

#include <memory>
#include <string>
#include <map>
#include <stdexcept>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <LuaState.h>
#pragma GCC diagnostic pop

#include "log_manager.hpp"

namespace engine {

	class config_manager {
	private:
		std::map<std::string, std::unique_ptr<lua::State>> m_files;
	
	public:
		config_manager();
		~config_manager();
	
		lua::State& get(const char *file);
	};
	
	typedef std::unique_ptr<config_manager> config_manager_ptr;
	extern config_manager_ptr cfg_mngr;
	#define CFG_DECL() engine::config_manager_ptr engine::cfg_mngr
}
