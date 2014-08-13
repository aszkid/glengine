#include "engine/sys/gui/base.hpp"

#include "engine/sys/gui/layout.hpp"

using namespace engine::gui;

base::base()
	: m_viewport(nullptr)
{}
base::~base()
{}

void base::draw() {}

void base::set_viewport(glm::ivec2 *viewport)
{
	m_viewport = viewport;
}
