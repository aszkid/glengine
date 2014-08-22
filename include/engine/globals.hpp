#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>

//#include <codecvt> - just VC++

#include "log_manager.hpp"
#include "config_manager.hpp"

#define MKSTR(stream)                                             \
  ( ( dynamic_cast<std::ostringstream &> (                             \
         std::ostringstream() . seekp( 0, std::ios_base::cur ) << stream )   \
    ) . str() )

#define METHODSTR std::string(typeid(*this).name()) + std::string("::") +  std::string(__func__) + std::string("()")

#if defined(__linux__)
	#define OS_LINUX
#elif defined(_WIN32)
	#define OS_WINDOWS
#endif

typedef unsigned int uint;

namespace engine {

	enum class SYSid : uint {
		input,
		gui,
		gstate
	};
	
	std::wstring cstr_to_wstr(const std::string str);
	
	struct exit_exception { 
		int c;
		exit_exception(int c) : c(c) {}
	};
	#define EXIT_EXCEPT(c) throw engine::exit_exception(c);
	
}
