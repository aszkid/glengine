#include "engine/sys/gui/layout.hpp"

#include "engine/sys/gui/base.hpp"

using namespace engine::gui;

layout::layout(glm::ivec2 *viewport, glm::mat4 *viewprojmat)
	: m_viewport(viewport), m_viewprojmat(viewprojmat)
{
}
layout::~layout()
{}

base* layout::add_component(base *component)
{
	m_components.emplace_back(component);
	m_components.back()->set_viewport(m_viewport);
	return m_components.back().get();
}
void layout::draw()
{
	for(auto& comp : m_components) {
		comp->draw();
	}
}
glm::ivec2* layout::get_viewport()
{
	return m_viewport;
}
glm::mat4* layout::get_viewproj_mat()
{
	return m_viewprojmat;
}
