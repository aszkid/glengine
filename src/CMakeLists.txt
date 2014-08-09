SET(SRCS
	main2.cpp
	screens/simple.cpp
)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

prepend_str(SRCS ${PROJECT_SOURCE_DIR}/src/)

ADD_EXECUTABLE(milsim ${SRCS})

TARGET_LINK_LIBRARIES(milsim engine)

## link extlibs
TARGET_LINK_LIBRARIES(milsim glfw ${GLFW_LIBRARIES})
TARGET_LINK_LIBRARIES(milsim GLEW ${GLEW_LIBRARIES})
## --------------------------
