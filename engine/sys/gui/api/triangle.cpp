#include "engine/sys/gui/api/triangle.hpp"

using namespace engine::gui::api;

triangle::triangle(const std::array<glm::vec2, 3> verts, const glm::vec4 color)
	: m_verts(verts), m_color(color)
{
	
	std::array<vert_t, 3> vert_dat;
	
	// populate vertex data
	vert_dat[0].pos = m_verts[0];
	vert_dat[1].pos = m_verts[1];
	vert_dat[2].pos = m_verts[2];
	vert_dat[0].col = m_color;
	vert_dat[1].col = m_color;
	vert_dat[2].col = m_color;
	
	// generate gl objects
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);
	
	// upload data to gpu
	glBindVertexArray(m_vao);
	
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, vert_dat.size() * sizeof(vert_t), &vert_dat[0], GL_DYNAMIC_DRAW);
		
	
	glBindVertexArray(0);
	
}
triangle::~triangle()
{}

void triangle::draw()
{}
