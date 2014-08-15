#include "engine/config_manager.hpp"

using namespace engine;

config_manager::config_manager()
{}
config_manager::~config_manager()
{}

lua::State& config_manager::get(const char *file)
{
	if(m_files.find(file) == m_files.end()) {
		LOG("CFGMANAGER", "Loading new config file (" << file << ").");
		try {
			m_files[file] = std::unique_ptr<lua::State>(new lua::State());
			m_files[file]->doFile(file);
		} catch(lua::RuntimeError& err) {
			throw std::runtime_error(MKSTR("LUA ERROR: " << err.what()));
		}
	}
	else
		LOG("CFGMANAGER", "File already loaded (" << file << ").");
	
	return *m_files[file].get();
}

