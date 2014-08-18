#include "engine/sys/gui/helpers.hpp"

using namespace engine;

	void gui::add_text(vertex_buffer_t * buffer, texture_font_t * font, const wchar_t * text, vec4 * color, vec2 * pen)
	{
		size_t i;
		float r = color->red, g = color->green, b = color->blue, a = color->alpha;
		for(i = 0; i < wcslen(text); ++i) {
			texture_glyph_t *glyph = texture_font_get_glyph(font, text[i]);
			if( glyph != NULL )
			{
				float kerning =  0.0f;
				if( i > 0)
				{
				kerning = texture_glyph_get_kerning( glyph, text[i-1] );
				}
				pen->x += kerning;

			
				float x0 = (int)(pen->x + glyph->offset_x);
				float y0 = (int)(pen->y - glyph->offset_y + (font->height - abs(font->descender) - 13.0*(font->height)/100.0));
				float x1 = (int)(x0 + glyph->width);
				float y1 = (int)(y0 + glyph->height);

				float s0 = glyph->s0;
				float t0 = glyph->t0;
				float s1 = glyph->s1;
				float t1 = glyph->t1;
				
				GLuint indices[6] = {0,1,2, 0,2,3};
				glyph_vertex_t vertices[4] = { { x0,y0,0,  s0,t0,  r,g,b,a },
					     { x0,y1,0,  s0,t1,  r,g,b,a },
					     { x1,y1,0,  s1,t1,  r,g,b,a },
					     { x1,y0,0,  s1,t0,  r,g,b,a } };
				vertex_buffer_push_back( buffer, vertices, 4, indices, 6 );
				pen->x += glyph->advance_x;
			
			
			}
		}
}

