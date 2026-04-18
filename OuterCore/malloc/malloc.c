#include "malloc.h"

void myFree(void *ptr)
{
	printf("free called\n");
}

void *myMalloc(size_t size)
{
	printf("malloc called\n");
}
void *myRealloc(void *ptr, size_t size)
{
	printf("realloc called\n");
}