#include "engine/sys/gui/components/label.hpp"

#include "engine/sys/gui/layout.hpp"

using namespace engine::gui::component;

label::label(layout *par_layout, glm::vec2 pos)
	: engine::gui::base(par_layout)
{
	m_prog.add_shader(GL_FRAGMENT_SHADER, "../../../rundir/shaders/text_frag.glsl");
	m_prog.add_shader(GL_VERTEX_SHADER, "../../../rundir/shaders/text_vert.glsl");
	m_prog.link();
	m_prog.use();
	
	m_atlas = texture_atlas_new(512, 512, 1);
	m_font = texture_font_new_from_file(m_atlas, 20, "../../../rundir/fonts/encode-sans/EncodeSansNormal-500-Medium.ttf");
	wchar_t *text = L"OpenMilSim v1.0 [0x026989]";
	m_buffer = vertex_buffer_new("vertex:3f,tex_coord:2f,color:4f");
	
	vec2 pen = {{50, 50}};
	vec4 col = {{0.1, 0.1, 0.1, 1}};
	
	texture_font_load_glyphs(m_font, text);
	
	size_t i;
	float r = col.red, g = col.green, b = col.blue, a = col.alpha;
	for(i = 0; i < wcslen(text); ++i) {
		texture_glyph_t *glyph = texture_font_get_glyph(m_font, text[i]);
		if( glyph != NULL )
		{
		    float kerning =  0.0f;
		    if( i > 0)
		    {
			kerning = texture_glyph_get_kerning( glyph, text[i-1] );
		    }
		    pen.x += kerning;
		    int x0  = (int)( pen.x + glyph->offset_x );
		    int y0  = (int)( pen.y + glyph->offset_y );
		    int x1  = (int)( x0 + glyph->width );
		    int y1  = (int)( y0 - glyph->height );
		    float s0 = glyph->s0;
		    float t0 = glyph->t0;
		    float s1 = glyph->s1;
		    float t1 = glyph->t1;
		    GLuint indices[6] = {0,1,2, 0,2,3};
		    vertex_t vertices[4] = { { x0,y0,0,  s0,t0,  r,g,b,a },
			                     { x0,y1,0,  s0,t1,  r,g,b,a },
			                     { x1,y1,0,  s1,t1,  r,g,b,a },
			                     { x1,y0,0,  s1,t0,  r,g,b,a } };
		    vertex_buffer_push_back( m_buffer, vertices, 4, indices, 6 );
		    pen.x += glyph->advance_x;
		}
	}
	
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
