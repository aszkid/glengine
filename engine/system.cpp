#include "engine/system.hpp"

using namespace engine;

sys_except::sys_except()
	: std::runtime_error("")
{}



system::system() {}
system::~system() {}

void system::init() {}
void system::shut_down() {}
void system::update(float dt) {}
