#pragma once

#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "helpers.hpp"

namespace engine {

	namespace gui {
	
		class base;
		typedef std::unique_ptr<base> component_ptr;
	
		class layout {
			std::vector<component_ptr> m_components;
		public:
			layout(glm::ivec2 *viewport, glm::mat4 *viewprojmat, mouse_state *mouse);
			~layout();
			
			glm::ivec2 *m_viewport;
			glm::mat4 *m_viewprojmat;
			mouse_state *m_mouse;
			
			base* add_component(base *component);
			void draw();
			void update();
		
		};
		
		// CHECK THIS OUT M8: https://gcc.gnu.org/onlinedocs/gcc/Variadic-Macros.html
		#define GUI_NEW_COMPONENT(type, layout, ...) dynamic_cast<type*>(layout->add_component(new type(layout, ## __VA_ARGS__)))
	
	}

}
