#include "engine/sys/gui/base.hpp"

#include "engine/sys/gui/layout.hpp"

using namespace engine::gui;

base::base(layout *par_layout)
	: m_layout(par_layout)
{}
base::~base()
{}

base* base::add_child(base *child)
{
	m_children.push_back(std::unique_ptr<base>(child));
	return m_children.back().get();
}
