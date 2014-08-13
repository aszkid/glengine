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
			typedef base* component_raw_ptr;
		private:
			std::vector<component_ptr> m_components;
			glm::ivec2 *m_viewport;
		public:
			layout(glm::ivec2 *viewport);
			~layout();
			
			void add_component(component_raw_ptr component);
			void draw();
		
		};
	
	}

}
