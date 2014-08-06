#include "libname/mylib.h"

void mylib_init(mylib_t *obj)
{
	obj->what = 14;
	obj->is[0] = '\0';
	obj->that = malloc(32);
}

void mylib_close(mylib_t *obj)
{
	obj->what = 0;
	obj->is[0] = '\0';
	free(obj->that);
}
