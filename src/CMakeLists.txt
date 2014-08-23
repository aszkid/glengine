SET(SRCS
	main.cpp
	
	# game states
	states/main_screen.cpp
)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

prepend_str(SRCS ${PROJECT_SOURCE_DIR}/src/)

ADD_EXECUTABLE(milsim ${SRCS})

TARGET_LINK_LIBRARIES(milsim engine)

## link extlibs - if needed
