#pragma once

#include <GL/glew.h>

// include layout (2D)
#include "engine/sys/gui/layout.hpp"
// include scene (3D)
// #include "engine/sys/render/scene.hpp"

#include <memory>

namespace engine {

	namespace gstate {
	
		class state {
		protected:
			gui::layout *m_layout;
			// render::scene *m_scene; TODO implement renderer
		
			// Either of these pointers can be null; then we have a 'simple' state (just GUI or just 3D)
			// If both are pointing to a valid object, then we have a combined state, which renders both 3D (first) and then GUI
			// --------
			// TODO: inactive states: everything is loaded in memory? lazy loading?
		
		public:
			state(gui::layout *layout);
			virtual ~state();
			
			virtual void stop() = 0;
			virtual void update(float dt) = 0;
			virtual void draw() = 0;
			virtual state* is_over() = 0;	// think about state switching. hard.
		};
		
		typedef std::unique_ptr<state> state_ptr;
	
	}

}
