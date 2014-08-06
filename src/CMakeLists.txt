SET(SRCS
	mylib.c
)

SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

prepend_str(SRCS ${PROJECT_SOURCE_DIR}/src/)

ADD_LIBRARY(mylib ${SRCS})

## link extlibs
#TARGET_LINK_LIBRARIES(audio anextlib)
## --------------------------
