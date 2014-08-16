#include "engine/sys/gui/components/label.hpp"

#include "engine/sys/gui/layout.hpp"

using namespace engine::gui::component;

label::label(layout *par_layout, const wchar_t *text, int size, const glm::vec2 pos, const char* fontfile)
	: engine::gui::base(par_layout)
{
	m_prog.add_shader(GL_FRAGMENT_SHADER, "../../../rundir/shaders/textnew_frag.glsl");
	m_prog.add_shader(GL_VERTEX_SHADER, "../../../rundir/shaders/textnew_vert.glsl");
	m_prog.link();
	
	auto& guidat = cfg_mngr->get("../../../rundir/cfg/gui.lua");
	std::string fontfinal = "../../../rundir/fonts/";
	
	// no panic
	if(fontfile[0] == '\0')
		fontfinal += static_cast<const char*>(guidat["font_std"]["name"]);
	else
		fontfinal += fontfile;
	if(size == -1)
		size = guidat["font_std"]["size"];
	
	m_atlas = texture_atlas_new(512, 512, 1);
	m_font = texture_font_new_from_file(m_atlas, size, fontfinal.c_str());
	m_buffer = vertex_buffer_new("vertex:3f,_tex_coord:2f,_color:4f");
	
	vec2 pen = {{pos.x, /*(m_layout->m_viewport->y - m_font->height) / 2*/ pos.y}};
	vec4 col = {{0.1, 0.1, 0.1, 1}};
	
	texture_font_load_glyphs(m_font, text);
	add_text(m_buffer, m_font, text, &col, &pen);	
	
	texture_font_delete(m_font);
	
	
	m_uni_mat = m_prog.get_uni_loc("viewProjMat");
	m_uni_tex = m_prog.get_uni_loc("_tex");
}
label::~label()
{}

void label::draw()
{	
	m_prog.use();
	glBindTexture(GL_TEXTURE_2D, m_atlas->id);
	glUniform1i(m_uni_tex, 0);
	glUniformMatrix4fv(m_uni_mat, 1, GL_FALSE, glm::value_ptr(*m_layout->m_viewprojmat));
	vertex_buffer_render(m_buffer, GL_TRIANGLES);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void label::update()
{
	
}
