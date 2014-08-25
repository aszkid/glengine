#include "engine/sys/gui/components/image.hpp"

#include "engine/sys/gui/layout.hpp"

#include <SOIL.h>

using namespace engine::gui::component;

image::image(layout *par_layout, const std::string file, glm::vec2 pos, glm::vec2 size)
	: engine::gui::base(par_layout), m_file(file), m_pos(pos), m_size(size)
{
	m_prog.add_shader(GL_FRAGMENT_SHADER, "../../../rundir/shaders/tex_frag.glsl");
	m_prog.add_shader(GL_VERTEX_SHADER, "../../../rundir/shaders/tex_vert.glsl");
	m_prog.link();
	
	// -------
	
	m_verts[0].m_pos =    glm::vec2(0, 0);
	m_verts[0].m_tcoord = glm::vec2(0, 0);
	m_verts[1].m_pos =    glm::vec2(m_size.x, 0);
	m_verts[1].m_tcoord = glm::vec2(1, 0);
	m_verts[2].m_pos =    glm::vec2(m_size.x, m_size.y);
	m_verts[2].m_tcoord = glm::vec2(1, 1);
	m_verts[3].m_pos =    glm::vec2(0, m_size.y);
	m_verts[3].m_tcoord = glm::vec2(0, 1);
	
	for(auto& v : m_verts) {
		v.m_pos += m_pos;
	}
	
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	
	glBufferData(GL_ARRAY_BUFFER, m_verts.size() * sizeof(vert_t), &m_verts[0], GL_STATIC_DRAW);
	
	glGenBuffers(1, &m_ebo);

	GLuint elems[] = {
		0, 1, 2,
		2, 3, 0
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elems), elems, GL_STATIC_DRAW);
	
	int w, h;
	unsigned char *img = SOIL_load_image(
		MKSTR("../../../rundir/img/" << m_file).c_str(),
		&w, &h, 0, SOIL_LOAD_RGB
	);
	glGenTextures(1, &m_texid);
	glBindTexture(GL_TEXTURE_2D, m_texid);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	SOIL_free_image_data(img);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	// -------
	
	m_uni_mat = glGetUniformLocation(m_prog.m_id, "viewProjMat");
	m_uni_tex = glGetUniformLocation(m_prog.m_id, "_tex");
}
image::~image()
{}

void image::handle_event()
{}

void image::update()
{}
void image::draw()
{
	m_prog.use();
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBindTexture(GL_TEXTURE_2D, m_texid);
	
	glUniformMatrix4fv(m_uni_mat, 1, GL_FALSE, glm::value_ptr(*m_layout->m_viewprojmat));
	m_prog.set_attrib_ptr("pos", 2, GL_FLOAT, GL_FALSE, sizeof(vert_t), 0);
	m_prog.set_attrib_ptr("_texCoord", 2, GL_FLOAT, GL_FALSE, sizeof(vert_t), (void*)(sizeof(glm::vec2)));
	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
