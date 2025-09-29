#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <deque>
#include <list>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <stdio.h>
#include <cmath>
#include <limits>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <map>
#include <queue>
#include <limits>
#include <exception>

class PmergeMe
{
	private:
		std::vector<int> _vectorBase;
		std::deque<int> _dequeBase;
		size_t _size;
		clock_t _managementTime;

	public:
        PmergeMe();
		PmergeMe(char** list);
		PmergeMe(PmergeMe const & src);
		PmergeMe & operator=(PmergeMe const & src);
		~PmergeMe();
		void pushswap();
		void mergeVector(std::vector<int>& vector);
		void mergeDeque(std::deque<int>& deque);
		int Jacobsthalnbr(int n);
		
		/* void PairInsertionSort(std::vector<int>& vec);
		void PairInsertionSort(std::deque<int>& deq); */
};

#endif