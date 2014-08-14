#include "engine/sys/gui/base.hpp"

#include "engine/sys/gui/layout.hpp"

using namespace engine::gui;

base::base(layout *par_layout)
	: m_layout(par_layout)
{}
base::~base()
{}

void base::draw() {}
void base::update() {}
