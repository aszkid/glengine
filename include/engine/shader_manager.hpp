#pragma once

#include <memory>
#include <map>

#include "engine/tools/shader.hpp"

namespace engine {

	class shader_manager {
	public:
		typedef std::unique_ptr<tools::shader_program> program_ptr;
	private:
		std::map<std::string, program_ptr> m_progs;
		
		bool program_exists(const std::string name);
	
	public:	
		shader_manager();
		~shader_manager();
		
		tools::shader_program* get_program(const std::string name);
	};

	typedef std::unique_ptr<shader_manager> shader_manager_ptr;
	extern shader_manager_ptr shdr_mngr;
	#define SHDR_DECL() engine::shader_manager_ptr engine::shdr_mngr;

}
