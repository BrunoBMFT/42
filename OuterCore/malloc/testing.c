#include "malloc.h"

int	main(void)
{
	void *random = myMalloc(10);
	myFree(random);
	random = myRealloc(NULL, 10);
	return 0;
}