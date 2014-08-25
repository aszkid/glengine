#include "engine/profiler.hpp"

using namespace engine;

profiler::profiler(std::string name)
	: m_name(name)
{
	m_beg = std::chrono::steady_clock::now();
}

profiler::~profiler()
{
	m_diff = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_beg);
	LOG("profiler", log::DEBUG) << '(' << m_name << ") " << m_diff.count() << " ms.";
}
