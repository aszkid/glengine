#include "engine/config_manager.hpp"

using namespace engine;

config_manager::config_manager()
{}
config_manager::~config_manager()
{}

sol::state& config_manager::get(const char *file)
{
	if(m_files.find(file) == m_files.end()) {
		LOG("cfg_mngr", log::INFO) << "Loading new config file (" << file << ").";
		try {
			m_files[file] = std::unique_ptr<sol::state>(new sol::state());
			m_files[file]->open_file(file);
		} catch(sol::error& err) {
			throw std::runtime_error(err.what());
		}
	}
	
	return *m_files[file].get();
}

