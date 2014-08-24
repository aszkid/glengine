SET(SRCS
	SOIL.c
	image_helper.c
	image_DXT.c
	stb_image_aug.c
)

prepend_str(SRCS ${PROJECT_SOURCE_DIR}/ext/soil/)

ADD_LIBRARY(soil STATIC ${SRCS})
