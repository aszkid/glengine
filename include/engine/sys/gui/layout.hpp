#pragma once

#include <vector>
#include <memory>

#include <glm/glm.hpp>

namespace engine {

	namespace gui {
	
		class base;
	
		class layout {
		public:
			typedef std::unique_ptr<base> component_ptr;
		private:
			std::vector<component_ptr> m_components;
		public:
			layout(glm::ivec2 *viewport, glm::mat4 *viewprojmat);
			~layout();
			
			glm::ivec2 *m_viewport;
			glm::mat4 *m_viewprojmat;
			
			base* add_component(base *component);
			void draw();
		
		};
	
	}

}
