#include "engine/sys/gui/components/image.hpp"

#include "engine/sys/gui/layout.hpp"

using namespace engine::gui::component;

image::image(layout *par_layout, const std::string file, glm::vec2 pos, glm::vec2 size)
	: engine::gui::base(par_layout), m_file(file), m_pos(pos), m_size(size)
{}
image::~image()
{}

void image::handle_event()
{}

void image::update()
{}
void image::draw()
{}
