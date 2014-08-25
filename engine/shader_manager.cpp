#include "engine/shader_manager.hpp"

using namespace engine;

shader_manager::shader_manager()
{}
shader_manager::~shader_manager()
{}

bool shader_manager::program_exists(const std::string name)
{
	return m_progs.find(name) != m_progs.end();
}

tools::shader_program* shader_manager::get_program(const std::string name)
{
	if(!program_exists(name)) {
		m_progs[name] = std::unique_ptr<tools::shader_program>(new tools::shader_program());
		LOG("shdr_mngr", log::INFO) << "Creating shader program '" << name << "'.";
	}
	return m_progs[name].get();
}
