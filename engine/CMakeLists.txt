SET(SRCS
	core.cpp
	system.cpp
	globals.cpp

	event.cpp
	event_manager.cpp
	config_manager.cpp
	log_manager.cpp
	
	tools/shader.cpp
	
	sys/input.cpp
	
	sys/gui.cpp
	sys/gui/base.cpp
	sys/gui/layout.cpp
	sys/gui/helpers.cpp
	sys/gui/components/button.cpp
	sys/gui/components/window.cpp
	sys/gui/components/label.cpp
)

SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

prepend_str(SRCS ${PROJECT_SOURCE_DIR}/engine/)

ADD_LIBRARY(engine ${SRCS})

## link extlibs
TARGET_LINK_LIBRARIES(engine glfw ${GLFW_LIBRARIES})
TARGET_LINK_LIBRARIES(engine GLEW ${GLEW_LIBRARIES})
TARGET_LINK_LIBRARIES(engine lua${LUA_VERSION} ${LUA_LIBRARIES})
TARGET_LINK_LIBRARIES(engine ${FREETYPE_LIBRARIES})
TARGET_LINK_LIBRARIES(engine freetype-gl)
## --------------------------
