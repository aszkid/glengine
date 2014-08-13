#include "engine/sys/gui/layout.hpp"

#include "engine/sys/gui/base.hpp"

using namespace engine::gui;

layout::layout(glm::ivec2 *viewport)
	: m_viewport(viewport)
{
}
layout::~layout()
{}

void layout::add_component(component_raw_ptr component)
{
	m_components.emplace_back(component);
	m_components.back()->set_viewport(m_viewport);
}
void layout::draw()
{
	for(auto& comp : m_components) {
		comp->draw();
	}
}
