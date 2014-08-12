#pragma once

#include "../base.hpp"
#include "engine/tools/shader.hpp"

namespace engine { namespace gui {

	namespace components {
	
		class button : public base {
		private:
			tools::shader_program m_shaderprog;
		public:
			button();
			~button();
			
			void draw();
		};
	
	}

}}
