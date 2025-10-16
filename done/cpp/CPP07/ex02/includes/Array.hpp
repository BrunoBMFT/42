#ifndef ARRAY_HPP
# define ARRAY_HPP
#include <iostream>
#include <stdlib.h>
#include <iostream>

template <typename var>
class Array
{
	private:
		var			*arr;
		unsigned int _size;
	public:
		Array() : arr(NULL), _size(0) {}
		Array(unsigned int n) {
			_size = n;
			arr = new var[_size];
		}
		Array(const Array& oth) {
			arr = NULL;
			_size = 0;
			*this = oth;
		}
		~Array() {
			delete[] arr;
		}
		
		Array& operator=(const Array& oth) {
			if (this == &oth)
				return *this;

			delete[] arr;

			if (oth.size() != 0) {
				_size = oth.size();
				arr = new var[_size];
				for (unsigned int i = 0; i < _size; i++)
					arr[i] = oth.arr[i];
			}
			return *this;
		}
		var& operator[](unsigned int num){
			if (num >= _size)
				throw InvalidIndex();
			return (arr[num]);
		}

		unsigned int size() const {
			return _size;
		}
	
	class InvalidIndex : public std::exception {
		public:
			virtual const char * what () const throw(){
				return ("Invalid index");
			}
	};
};



#endif