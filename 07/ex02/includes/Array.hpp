#ifndef ARRAY_HPP
# define ARRAY_HPP
#include <iostream>
#include <stdlib.h>
#include <iostream>

template <typename var>
class Array
{
	private:
		var		*arr;
		size_t	size;
	public:
		Array() {
			arr = NULL;
		}
		Array(unsigned int n) {
			size = n;
			arr = new var[n];
			for (size_t i = 0; i < n; i++)
				arr[i] = rand() % 100;
		}

		var operator[](size_t num){
			if (num > size)
				throw InvalidIndex();
			return (arr[num]);
		}










	//exceptions
	class InvalidIndex : public std::exception {
		public:
			virtual const char * what () const throw(){
				return ("Invalid index");
			}
	};
};



#endif