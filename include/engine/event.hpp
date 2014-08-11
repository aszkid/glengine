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
		INPUT_WIN_SIZE = 1 << 3
	};

}
