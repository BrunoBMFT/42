#include "PmergMe.hpp"

void	printBefore(char **av)
{
	std::cout << "Before: \n";
	for (int i = 1; av[i]; i++)
		std::cout << av[i] << " ";
	std::cout << "\n";
}

void	printAfter(List main)
{
	std::cout << "After: \n";
	for (ListIt it = main.begin(); it != main.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n";
}

void	printList(std::string str, pairList list, int addVal) {
	std::cout << str << ": \n";
	for (pairListIt it = list.begin(); it != list.end(); it++) {
			std::cout << it->first << " " << it->second << " ";
	}
	std::cout << "\t addVal: " << addVal;
	std::cout << "\n";
}


void	printMainAndPend(std::string str, List main, pairList list, int addVal) {
	std::cout << str << ": \n";

	for (ListIt it = main.begin(); it != main.end(); it++)
		std::cout << *it << " ";

	std::cout << "\t pend:";
	for (pairListIt it = list.begin(); it != list.end(); it++)
			std::cout << it->first << " " << it->second << " ";
	std::cout << "\t addVal: " << addVal;
	std::cout << "\n";
}


void	createPairList(char **av, pairList *list, int *addVal)
{
	int i = 1;

	while (av[i]) {
		if (av[i] && av[i + 1]) {
			Pair temp(std::atoi(av[i]), std::atoi(av[i + 1]));
			list->push_back(temp);
			i += 2;
		}
		else {
			*addVal = std::atoi(av[i]);
			i++;
		}
	}
}

void	sortPairs(pairList *list)
{
	for (pairListIt it = list->begin();
		it != list->end(); it++) {
		if (it->first > it->second) {
			int temp = it->first;
			it->first = it->second;
			it->second = temp;
		}
	}
}

bool	secondCompare(Pair a, Pair b) {
	if (a.second < b.second)
		return 1;
	return 0;
}

void	mergeSort(pairListIt start, pairListIt end, size_t size)
{
	if (size == 0 && start != end)
		size = std::distance(start, end);
	if (size <= 1)
		return ;
	size_t firstHalf = size / 2;
	size_t secondHalf = size - firstHalf;
	pairListIt center = start;
	std::advance(center, firstHalf);
	mergeSort(start, center, firstHalf);
	mergeSort(center, end, secondHalf);
	std::inplace_merge(start, center, end, &secondCompare);//this sorts 2 sorted halfs, meaning from start to center its sorted, and from center to end is sorted
}


void	createMain(List *main, pairList list)
{
	for (pairListIt it = list.begin(); it != list.end(); it++)
		main->push_back(it->second);
	
	if (!list.empty())
		main->push_front(list.begin()->first);
	//first of pend will be first in main, since its always smallest
}

void	PmergeMeList(char **av)
{
	pairList list;
	List main;
	int addVal = -1;//if size is odd
	// printBefore(av);

	createPairList(av, &list, &addVal);
	printList("before sortPairs", list, addVal);
	sortPairs(&list);
	printList("after sortPairs", list, addVal);
	mergeSort(list.begin(), list.end(), 0);
	printList("after mergeSort", list, addVal);
	
	createMain(&main, list);
	printMainAndPend("created Main and Pend", main, list, addVal);

	// printAfter(main);
}