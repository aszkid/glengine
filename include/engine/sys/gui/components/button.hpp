#pragma once

#include "../base.hpp"
#include "engine/tools/shader.hpp"

namespace engine { namespace gui {

	namespace component {
	
		class button : public base {
		private:
			tools::shader_program m_prog;
			glm::vec2 m_pos;
		public:
			button();
			~button();
			
			void draw();
		};
	
	}

}}
