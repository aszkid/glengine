#include "engine/sys/gui/layout.hpp"

#include "engine/sys/gui/base.hpp"

using namespace engine::gui;

layout::layout(glm::ivec2 *viewport, glm::mat4 *viewprojmat, glm::vec2 *mouse)
	: m_viewport(viewport), m_viewprojmat(viewprojmat), m_mouse(mouse), m_event(nullptr)
{
}
layout::~layout()
{}

base* layout::new_component(base *component)
{
	m_components.emplace_back(component);
	return m_components.back().get();
}
void layout::draw()
{
	for(auto& comp : m_components) {
		comp->draw();
	}
}
void layout::update()
{
	for(auto& comp : m_components) {
		comp->update();
	}
}
void layout::handle_event(event_t *ev)
{
	m_event = ev;
	for(auto& comp : m_components) {
		comp->handle_event();
	}
}
