#include "engine/sys/gui/base.hpp"

#include "engine/sys/gui/layout.hpp"

using namespace engine::gui;

base::base(glm::ivec2 *viewport, glm::mat4 *viewprojmat)
	: m_viewport(viewport), m_viewprojmat(viewprojmat)
{}
base::~base()
{}

void base::draw() {}

void base::set_viewport(glm::ivec2 *viewport)
{
	m_viewport = viewport;
}
