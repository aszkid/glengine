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
log_instance::log_instance(logger *parent)
	: m_parent(parent)
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
	m_loggers[name] = std::unique_ptr<logger>(new logger(name));
}
log_instance log_manager::get(const std::string &name)
{
	if(m_loggers.find(name) == m_loggers.end()) {
		make(name);
	}

	return log_instance(m_loggers[name].get());
}
