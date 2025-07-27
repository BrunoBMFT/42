#ifndef WHATEVER_HPP
# define WHATEVER_HPP


template <typename var>
void swap(var& a, var& b){
	var temp = a;
	a = b;
	b = temp;
}

template <typename var>
var max(var a, var b){
	if (a > b)
		return a;
	return b;
}

template <typename var>
var min(var a, var b){
	if (a < b)
		return a;
	return b;
}

#endif