#include <stdio.h>
#include <stdlib.h>

#include <libname/mylib.h>

int main(int argc, char** argv)
{
	mylib_t obj;
	mylib_init(&obj);
	
	printf("My library works: %i.\n", obj.what);
	
	mylib_close(&obj);
	
	return 0;
}
