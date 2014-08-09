SET(SRCS
	main.cpp
)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

prepend_str(SRCS ${PROJECT_SOURCE_DIR}/src/)

ADD_EXECUTABLE(engine ${SRCS})

## link extlibs
#TARGET_LINK_LIBRARIES(audio anextlib)
## --------------------------
