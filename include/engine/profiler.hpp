#pragma once

#include <chrono>
#include <string>

#include "log_manager.hpp"

namespace engine {

	class profiler {
		typedef std::chrono::system_clock::time_point t_point;
		t_point m_beg;
		std::chrono::milliseconds m_diff;
		std::string m_name;
	public:	
		profiler(std::string name);
		~profiler();
	};
	
	#define PASTE_HELPER(a,b) a ## b
	#define PASTE(a,b) PASTE_HELPER(a,b)
	
	#if defined(__COUNTER__)
		#define PROFILE(n) profiler PASTE(__prof_, __COUNTER__)(n)
	#else
		#define PROFILE(n) profiler PASTE(__prof_, __LINE__)(n)
	#endif
	
}
