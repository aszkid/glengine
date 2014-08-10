#pragma once

#include <iostream>
#include <sstream>
#include <string>

#define LOG(t, msg) std::cout << "[" << t << "] " << msg << std::endl

#define MKSTR(stream)                                             \
  ( ( dynamic_cast<std::ostringstream &> (                             \
         std::ostringstream() . seekp( 0, std::ios_base::cur ) << stream )   \
    ) . str() )

#define METHODSTR std::string(typeid(*this).name()) + std::string("::") +  std::string(__func__) + std::string("()")

typedef unsigned int uint;

namespace engine {

	enum SYSid {
		cfg,
		input,
		render,
		log
	};

}
