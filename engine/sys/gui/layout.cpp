#include "engine/sys/gui/layout.hpp"

using namespace engine::gui;

layout::layout()
{}
layout::~layout()
{}

void layout::add_component(component_raw_ptr component)
{
	m_components.emplace_back(component);
}
void layout::draw()
{}
