#ifndef EASYFIND_HPP
# define EASYFIND_HPP
# include <iostream>
# include <algorithm>

template <typename Container>
typename Container::const_iterator easyfind(const Container& cntr, int tofind){
	typename Container::const_iterator found = std::find(cntr.begin(), cntr.end(), tofind);
	if (found == cntr.end())
		throw std::logic_error("Not found");
	return (found);
}


#endif