#include "engine/log_manager.hpp"

using namespace engine;

logger::logger(const logger &l)
{
	buff << l.buff.str();
}
logger& logger::operator=(const logger &l)
{
	buff << l.buff.str();
	return *this;
}

logger::logger()
{}
logger::~logger()
{
	std::cout << "[LOG] " << buff.str() << std::endl;
	buff.str(std::string());
	buff.clear();
}

log_manager::log_manager()
{}
log_manager::~log_manager()
{}

logger log_manager::get()
{
	return logger(); //here, it would be filled with ptr to its log_cfg
}
