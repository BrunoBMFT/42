#ifndef EASYFIND_HPP
# define EASYFIND_HPP
# include <vector>
# include <iostream>



template <typename T> T max(T a, T b){
	return (a > b ? a : b);
}

template <typename T> int easyfind(T container, int tofind){
	for (size_t i = 0; i < container.size(); i++){
		if (container[i] == tofind)
			return i;
	}
	return -1;// ANOTHER ERROR VALUE
}


#endif