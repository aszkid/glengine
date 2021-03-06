#pragma once

#include <vector>
#include <memory>
#include <type_traits>

#include <boost/config.hpp> // to check for c++11 features

#include <glm/glm.hpp>

#include "helpers.hpp"
#include "engine/event.hpp"

namespace engine {

	namespace gui {
	
		class base;
		typedef std::unique_ptr<base> component_ptr;
	
		class layout {
			std::vector<component_ptr> m_components;
		public:
			layout(glm::ivec2 *viewport, glm::mat4 *viewprojmat, glm::vec2 *mouse);
			~layout();
			
			glm::ivec2 *m_viewport;
			glm::mat4 *m_viewprojmat;
			glm::vec2 *m_mouse;
			event_t *m_event;
			
			void handle_event(event_t *ev);
			
			base* new_component(base *component);
			void draw();
			void update();
			
			#if !defined(BOOST_NO_VARIADIC_TEMPLATES)
				template<class T, typename... Args>
				typename std::enable_if<std::is_base_of<base, T>::value, T*>::type
				new_component(Args... args)
				{
					return static_cast<T*>(new_component(new T(this, args...)));
				}
			#endif
			
		};
		
		#if !defined(BOOST_NO_VARIADIC_MACROS)
			// CHECK THIS OUT M8: https://gcc.gnu.org/onlinedocs/gcc/Variadic-Macros.html
			#define GUI_NEW_COMPONENT(type, layout, ...) static_cast<type*>(layout->new_component(new type(layout, ## __VA_ARGS__)))
		#endif
			
	}

}
