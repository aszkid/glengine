SET(SRCS
	core.cpp
	system.cpp

	event.cpp
	event_manager.cpp
	
	tools/shader.cpp
	
	sys/input.cpp
	
	sys/gui.cpp
	sys/gui/base.cpp
	sys/gui/layout.cpp
	sys/gui/components/button.cpp
)

SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

prepend_str(SRCS ${PROJECT_SOURCE_DIR}/engine/)

ADD_LIBRARY(engine ${SRCS})

## link extlibs
TARGET_LINK_LIBRARIES(engine glfw ${GLFW_LIBRARIES})
TARGET_LINK_LIBRARIES(engine GLEW ${GLEW_LIBRARIES})
TARGET_LINK_LIBRARIES(engine lua${LUA_VERSION} ${LUA_LIBRARIES})
## --------------------------
