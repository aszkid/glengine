#pragma once

#include <vector>

#include "engine/globals.hpp"

namespace engine {

	struct event_t {
		event_t() {}
		event_t(uint channel) : m_channel(channel) {}
	
		uint m_channel; // let it be a keyboard, mouse, network, etc event
	};

	enum ev_channel : uint {
		INPUT_KEY = 1 << 0,
		INPUT_CHAR = 1 << 1,
		INPUT_MOUSE_BTN = 1 << 2,
		INPUT_WIN_SIZE = 1 << 3,
		INPUT_CURSOR_POS = 1 << 4
	};
	
	namespace events {
	
		struct input_key : public event_t {
			int m_key; int m_scancode; int m_action; int m_mods;
			
			input_key(uint channel, int key, int scancode, int action, int mods)
				: event_t(channel), m_key(key), m_scancode(scancode), m_action(action), m_mods(mods) {}
		};
		struct input_char : public event_t {
			unsigned int m_key;
			
			input_char(uint channel, unsigned int key)
				: event_t(channel), m_key(key) {}
		};
		struct input_mouse_btn : public event_t {
			int m_button; int m_action; int m_mods;
			
			input_mouse_btn(uint channel, int button, int action, int mods)
				: event_t(channel), m_button(button), m_action(action), m_mods(mods) {}
		};
		struct input_win_size : public event_t {
			 int m_x; int m_y;
			 
			input_win_size(uint channel, int x, int y)
				: event_t(channel), m_x(x), m_y(y) {}
		};
		struct input_cursor_pos : public event_t {
			double m_x; double m_y;
			
			input_cursor_pos(uint channel, double x, double y)
				: event_t(channel), m_x(x), m_y(y) {}
		};
	
	}

}
