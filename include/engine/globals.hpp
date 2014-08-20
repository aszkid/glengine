#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>

#include "log_manager.hpp"

#define MKSTR(stream)                                             \
  ( ( dynamic_cast<std::ostringstream &> (                             \
         std::ostringstream() . seekp( 0, std::ios_base::cur ) << stream )   \
    ) . str() )

#define METHODSTR std::string(typeid(*this).name()) + std::string("::") +  std::string(__func__) + std::string("()")


#define LOG(ch, lev) engine::log_mngr->get(ch, lev) << "(L:" << __LINE__ << ") "
#define LOG_IF(ch, lev, b) NLOG((b ? ch : "void"), lev)

#if defined(__linux__)
	#define OS_LINUX
#elif defined(_WIN32)
	#define OS_WINDOWS
#endif

typedef unsigned int uint;

namespace engine {

	enum class SYSid : uint {
		input,
		gui
	};
	
	std::wstring cstr_to_wstr(const char *str);
	
	struct exit_exception { 
		int c;
		exit_exception(int c) : c(c) {}
	};
	#define EXIT_EXCEPT(c) throw engine::exit_exception(c);
	
}
