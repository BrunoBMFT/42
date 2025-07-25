#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <iostream>
#include <stdlib.h>
#include <iostream>

template <typename T>
class Array {
	private:
		T				*_array;
		unsigned int	_size;
	public:
		// constructors
		Array() : _array(NULL), _size(0) {
			std::cout << "Default called, empty array" << std::endl;
		}
		Array(unsigned int n) : _size(n) {
			std::cout << "Constructor called, array of size " << _size << std::endl;
			_array = new T[_size];
		}
		Array(Array const &other) : _array(NULL), _size(0) {
			std::cout << "Copy Constructor called" << std::endl;
			*this = other;
		}
		//destructor
		~Array() {
			delete [] _array;
		}
		//operators
		Array &operator=(Array const &other) {
			std::cout << "Copy Assignement called" << std::endl;
			if (this == &other)
				return *this;
			delete [] _array;
			if (other.getSize() != 0) {
				_size = other.getSize();
				_array = new T[_size];
				for (unsigned int i = 0; i < _size; i++)
					_array[i] = other._array[i];
			}
			return *this;
		}
		T &operator[](unsigned int i){
			if (i >= _size)
				throw InvalidIndex();
			return _array[i];
		}

		unsigned int getSize() const {
			return _size;
		};

		//exceptions
		class InvalidIndex : public std::exception {
			public:
				virtual const char * what () const throw(){
					return ("Invalid index");
				}
		};
};

#endif