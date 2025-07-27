#ifndef ITER_HPP
# define ITER_HPP
# include <iostream>


template <typename var>
void iter(var *arr, size_t len, void (*func)(var &)){
	if (arr == NULL || func == NULL)
		return ;
	for (size_t i = 0; i < len; i++)	
		func(arr[i]);
}

#endif