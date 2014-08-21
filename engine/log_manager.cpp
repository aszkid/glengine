#include "engine/log_manager.hpp"

using namespace engine;

// logger
logger::logger(const std::string &name)
	: m_name(name)
{}
logger::~logger()
{}
void logger::handle(const std::string& val)
{
	// LOCK MUTEX TO AVOID RESOURCE RACES!!
	std::cout << "[LOG::" << m_name << "] " << val << std::endl;
}

// void logger
void_logger::void_logger(const std::string &name)
	: logger(name)
{}
void void_logger::handle(const std::string &val)
{
	// it's a void logger. it does nothing.
}


// log instance
log_instance::log_instance(const log_instance &l)
{
	m_buff << l.m_buff.str();
}
log_instance& log_instance::operator=(const log_instance &l)
{
	m_buff << l.m_buff.str();
	return *this;
}
log_instance::log_instance(logger *parent, int level)
	: m_parent(parent), m_level(level)
{}
log_instance::~log_instance()
{
	m_parent->handle(m_buff.str());
}

// log manager
log_manager::log_manager()
{}
log_manager::~log_manager()
{}

void log_manager::make(const std::string &name)
{
	make<logger>(name);
}
log_instance log_manager::get(const std::string &name, int level)
{
	if(m_loggers.find(name) == m_loggers.end()) {
		make(name);
	}

	return log_instance(m_loggers[name].get(), level);
}
