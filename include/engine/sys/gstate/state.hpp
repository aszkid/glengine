#pragma once

#include <GL/glew.h>
#include "engine/sys/gui/layout.hpp"

namespace engine {

	namespace gstate {
	
		class state {
			gui::layout *m_layout;
			// render::scene *m_scene; TODO implement renderer
		
			// Either of these pointers can be null; then we have a 'simple' state (just GUI or just 3D)
			// If both are pointing to a valid object, then we have a combined state, which renders both 3D (first) and then GUI
			// --------
			// Instead of creating 10 billion derived classes, use component-based design; create a state, add things to it, push it
			// to the state stack, render if active.
			// --------
			// TODO: inactive states: everything is loaded in memory? lazy loading?
		
		public:
			state();
			~state();
		};
	
	}

}
