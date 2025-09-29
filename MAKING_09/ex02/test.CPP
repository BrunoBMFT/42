#include "test.HPP"

PmergeMe::PmergeMe() {
	_vectorBase = std::vector<int>();
	_dequeBase = std::deque<int>();
	_size = 0;
	/* for (std::map<std::string, float>::iterator i = _dataBase.begin(); i != _dataBase.end(); ++i) 
        std::cout << i->first << " " << i->second << std::endl; */
}
PmergeMe::PmergeMe(char** list) {
	clock_t start = clock();
	//std::string input = list[1];
	//std::size_t found = input.find(' ');
	for (size_t i = 1; list[i]; i++)
    {
        for (size_t j = 0; list[i][j]; j++)
        {
            if (!isdigit(list[i][j]))
            {
                std::cerr << "Error: it needs to be all digits and only positive ones" << std::endl;
                exit (1);
            }
        }
		for (size_t k = 0; list[k]; k++)
		{
			if (list[i] == list[k] && i != k)
			{
				std::cerr << "Error: there are duplicate numbers" << std::endl;
				exit (1);
			}
		}
    }
	_vectorBase = std::vector<int>();
	_dequeBase = std::deque<int>();

	for (size_t i = 0; list[i]; i++) {
		_vectorBase.push_back(std::atoi(list[i]));
		_dequeBase.push_back(std::atoi(list[i]));
	}
	_size = _vectorBase.size();
	_managementTime = clock() - start;
}
PmergeMe::PmergeMe(const PmergeMe& other)
{
	*this = other;
}
PmergeMe &PmergeMe::operator=(const PmergeMe &src)
{
	if (this != &src)
	{
		_vectorBase = src._vectorBase;
		_dequeBase = src._dequeBase;
	}
	return *this;
}
PmergeMe::~PmergeMe()
{
	//std::cout << "PmergeMe descontructor called" << std::endl;
}

void PmergeMe::mergeVector(std::vector<int>& vector) {
	if (vector.size() <= 1)
		return;
	size_t mid = vector.size() / 2;
	std::vector<int> left(vector.begin(), vector.begin() + mid);
	std::vector<int> right(vector.begin() + mid, vector.end());
	mergeVector(left);
	mergeVector(right);
	std::merge(left.begin(), left.end(), right.begin(), right.end(), vector.begin());
}

void PmergeMe::pushswap() {
	std::cout << "Before: ";
	for (size_t i = 0; i < _size; i++)
		std::cout << _vectorBase[i] << " ";
	std::cout << std::endl;
	mergeVector(_vectorBase);
	std::cout << "After: ";
	for (size_t i = 0; i < _size; i++)
		std::cout << _vectorBase[i] << " ";
}

int PmergeMe::Jacobsthalnbr(int n) {
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	return Jacobsthalnbr(n - 1) + 2 * Jacobsthalnbr(n - 2);
}


//original
/*
void PmergeMe::mergeVector(std::vector<int>& vector) {
	if (vector.size() <= 1)
		return;
	size_t mid = vector.size() / 2;
	std::vector<int> left(vector.begin(), vector.begin() + mid);
	std::vector<int> right(vector.begin() + mid, vector.end());
	mergeVector(left);
	mergeVector(right);
	std::merge(left.begin(), left.end(), right.begin(), right.end(), vector.begin());
}

void PmergeMe::mergeDeque(std::deque<int>& deque) {
	if (deque.size() <= 1)
		return;
	size_t mid = deque.size() / 2;
	std::deque<int> left(deque.begin(), deque.begin() + mid);
	std::deque<int> right(deque.begin() + mid, deque.end());
	mergeDeque(left);
	mergeDeque(right);
	std::merge(left.begin(), left.end(), right.begin(), right.end(), deque.begin());
}

void PmergeMe::pushswap() {
	std::cout << "Before: ";
	for (size_t i = 0; i < _size; i++)
	{
		std::cout << _vectorBase[i] << " ";
	}
	std::cout << std::endl;
	clock_t vectorStart = clock();
	mergeVector(_vectorBase);
	clock_t vectorDuration = clock() - vectorStart;
	clock_t dequeStart = clock();
	mergeDeque(_dequeBase);
	clock_t dequeDuration = clock() - dequeStart;
	std::cout << "After: ";
	for (size_t i = 0; i < _size; i++)
	{
		std::cout << _vectorBase[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "Time to process a range of " << _size << " elements with std::vector : " << (double)(vectorDuration + _managementTime) * 100 / CLOCKS_PER_SEC << " us" << std::endl;
	std::cout << "Time to process a range of " << _size << " elements with std::deque : " << (double)(dequeDuration + _managementTime) * 100 / CLOCKS_PER_SEC << " us" << std::endl;
}

int PmergeMe::Jacobsthalnbr(int n) {
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	else
		return Jacobsthalnbr(n - 1) + 2 * Jacobsthalnbr(n - 2);
}
*/