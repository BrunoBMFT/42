#include "../includes/PmergeMe.hpp"

//*CONSTRUCTORS
PmergeMe::PmergeMe() {}//do
PmergeMe::PmergeMe(char **args)
{
	for (int i = 1; args[i]; i++) {
		unsigned int temp = atoi(args[i]);
		_vector.push_back(temp);
		//push back onto deque as well
	}
	_size = _vector.size();
	_vectorTime = 0.42;// todo hardcoded
	_dequeTime = 0.69;// todo hardcoded
}
PmergeMe::PmergeMe(const PmergeMe& oth) {
	*this = oth;
}
PmergeMe PmergeMe::operator=(const PmergeMe& oth)
{
	return (*this);
}
PmergeMe::~PmergeMe() {}



//*FUNCTIONS

void	PmergeMe::printUnsorted()
{
	std::cout << "Before:\t";
	for (int i = 0; i < _vector.size(); i++)
		std::cout << _vector[i] << " ";
	std::cout << std::endl;
}
void	PmergeMe::printSorted()
{
	std::cout << "After:\t";
	for (int i = 0; i < _vector.size(); i++)
		std::cout << _vector[i] << " ";
	std::cout << std::endl;
}
void	PmergeMe::printTimeVector() {
	std::cout << "Time to process a range of " << _size;
	std::cout << " elements with std::vector : " << _vectorTime;
	std::cout << " us" << std::endl;
}
void	PmergeMe::printTimeDeque() {
	std::cout << "Time to process a range of " << _size;
	std::cout << " elements with std::deque : " << _dequeTime;
	std::cout << " us" << std::endl;
}


//*EXCEPTIONS
const char *PmergeMe::Exception::what() const throw() {
	return ("ANY EXCEPTION LOL.");
}
//recursion will happen while (segment of the list / 2) < _size / 2


void	PmergeMe::sort()
{

}
