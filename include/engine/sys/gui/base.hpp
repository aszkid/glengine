#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <boost/config.hpp>

#include "engine/globals.hpp"

#include "engine/config_manager.hpp"

namespace engine {

	namespace gui {
		
		class layout;
		
		// base gui component
		class base {
		protected:
			GLuint m_uni_mat;
			layout *m_layout;
			std::vector<std::unique_ptr<base>> m_children;
			base *m_parent;
			bool m_dirty;
		public:
			base(layout *par_layout);
			virtual ~base();
			
			virtual void update();
			virtual void draw();
			
			base* add_child(base *child);
		#if !defined(BOOST_NO_VARIADIC_TEMPLATES)
			template<class T, typename... Args>
			typename std::enable_if<std::is_base_of<base, T>::value, T*>::type
			add_child(Args... args)
			{
				return static_cast<T*>(add_child(new T(m_layout, args...)));
			}
		#endif
		};
		
	}


}
