#ifndef MALLOC_H
# define MALLOC_H

#include <stdio.h>//printf

void myFree(void *ptr);
void *myMalloc(size_t size);
void *myRealloc(void *ptr, size_t size);

#endif