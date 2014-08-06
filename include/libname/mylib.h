#ifndef _MYLIB_H
#define _MYLIB_H

#include <stdlib.h>

typedef struct {
	int what;
	char is[4];
	void* that;
} mylib_t;

void mylib_init(mylib_t *obj);
void mylib_close(mylib_t *obj);

#endif
