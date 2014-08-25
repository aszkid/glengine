#include "engine/sys/gui/api/rectangle.hpp"

using namespace engine::gui::api;

rectangle::rectangle(glm::mat4 *viewprojmat, const glm::vec2 size, const glm::vec2 pos, const glm::vec4 color)
	: drawable(viewprojmat), m_size(size), m_pos(pos), m_color(color)
{
	m_prog = shdr_mngr->get_program("primitive");
	
	upload_init();
	
	m_uni_mat = m_prog->get_uni_loc("viewProjMatrix");
}
rectangle::~rectangle()
{}

std::array<rectangle::vert_t, 4>* rectangle::gen_vert_data()
{
	std::array<vert_t, 4> *vdat = new std::array<vert_t, 4>;
	vdat->at(0).pos = glm::vec2(0);
	vdat->at(1).pos = glm::vec2(0, m_size.y);
	vdat->at(2).pos = m_size;
	vdat->at(3).pos = glm::vec2(m_size.x, 0);
	vdat->at(0).col = m_color;
	vdat->at(1).col = m_color;
	vdat->at(2).col = m_color;
	vdat->at(3).col = m_color;
	
	for(auto& v : *vdat) {
		v.pos += m_pos;
	}
	
	return vdat;
}
void rectangle::upload()
{
	PROFILE("vbo_buffersubdata");

	// populate vertex data
	std::array<vert_t, 4> *vert_dat = gen_vert_data();
	
	// update buffer data
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vert_dat->size() * sizeof(vert_t), &(*vert_dat)[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	delete vert_dat;
}
void rectangle::upload_init()
{
	// populate vertex data
	std::array<vert_t, 4> *vert_dat = gen_vert_data();
	
	// populate index data
	std::array<GLuint, 6> index_dat;
	index_dat[0] = 0;
	index_dat[1] = 1;
	index_dat[2] = 2;
	index_dat[3] = 2;
	index_dat[4] = 3;
	index_dat[5] = 0;
	
	// generate gl objects
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);
	
	// upload data to gpu
	glBindVertexArray(m_vao);
	
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, vert_dat->size() * sizeof(vert_t), &(*vert_dat)[0], GL_DYNAMIC_DRAW);
		
		m_prog->set_attrib_ptr("position", 2, GL_FLOAT, GL_FALSE, sizeof(vert_t), 0);
		m_prog->set_attrib_ptr("color", 4, GL_FLOAT, GL_FALSE, sizeof(vert_t), (void*)(sizeof(glm::vec2)));
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_dat.size() * sizeof(GLuint), &index_dat[0], GL_STATIC_DRAW);
	
	glBindVertexArray(0);
	
	delete vert_dat;
}

void rectangle::draw()
{
	m_prog->use();
	
	glBindVertexArray(m_vao);
	
		glUniformMatrix4fv(m_uni_mat, 1, GL_FALSE, glm::value_ptr(*m_viewprojmat));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
	glBindVertexArray(0);
}

void rectangle::set_position(const glm::vec2 pos)
{
	m_pos = pos;
	upload();
}
void rectangle::set_color(const glm::vec4 color)
{
	m_color = color;
	upload();
}
