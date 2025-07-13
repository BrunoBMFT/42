#include "second.h"

void	modPutstr(char *str){
	int i;
	for (i = 0; str[i]; i++)
		write(1, &str[i], 1);
	printf("length: %d\n", i);
}