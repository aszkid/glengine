#include "engine/sys/gui/components/label.hpp"

#include "engine/sys/gui/layout.hpp"

using namespace engine::gui::component;

label::label(layout *par_layout, glm::vec2 pos)
	: engine::gui::base(par_layout)
{
	m_prog.add_shader(GL_FRAGMENT_SHADER, "../../../rundir/shaders/text_frag.glsl");
	m_prog.add_shader(GL_VERTEX_SHADER, "../../../rundir/shaders/text_vert.glsl");
	m_prog.link();
	
	m_atlas = texture_atlas_new(512, 512, 1);
	m_font = texture_font_new_from_file(m_atlas, 18, "../../../rundir/fonts/encode-sans/EncodeSansNormal-500-Medium.ttf");
	wchar_t *text = L"> inb4 op can't inb4. <> ^ € % :: == Some text, some text. This looks nice!";
	m_buffer = vertex_buffer_new("vertex:3f,tex_coord:2f,color:4f");
	
	vec2 pen = {{80, (m_layout->m_viewport->y - m_font->height) / 2.0}};
	vec4 col = {{0.1, 0.1, 0.1, 1}};
	
	texture_font_load_glyphs(m_font, text);
	add_text(m_buffer, m_font, text, &col, &pen);
	texture_font_delete(m_font);
	
	glBindTexture(GL_TEXTURE_2D, m_atlas->id);
	
	m_uni_mat = m_prog.get_uni_loc("viewProjMat");
	m_uni_tex = m_prog.get_uni_loc("texture");
	
}
label::~label()
{}

void label::draw()
{	
	m_prog.use();
	
	glUniform1i(m_uni_tex, 0);
	glUniformMatrix4fv(m_uni_mat, 1, GL_FALSE, glm::value_ptr(*m_layout->m_viewprojmat));
	
	vertex_buffer_render(m_buffer, GL_TRIANGLES);
}

void label::update()
{
	
}
