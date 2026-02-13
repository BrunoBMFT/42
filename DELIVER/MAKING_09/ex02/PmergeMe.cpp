#include "PmergeMe.hpp"

int	printBefore(char **av)
{
	std::cout << "Before:\t";
	int i = 1;
	for (; av[i]; i++)
		std::cout << av[i] << " ";
	std::cout << "\n";
	return (i - 1);
}


bool	secondCompare(Pair a, Pair b) {
	if (a.second < b.second)
		return 1;
	return 0;
}


//!List
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

void	sortPairsList(pairList *list)
{
	for (pairListIt it = list->begin(); it != list->end(); it++) {
		if (it->first > it->second) {
			int temp = it->first;
			it->first = it->second;
			it->second = temp;
		}
	}
}

void	mergeSortList(pairListIt start, pairListIt end, size_t size)
{
	if (size == 0 && start != end)
		size = std::distance(start, end);
	if (size <= 1)
		return ;
	size_t firstHalf = size / 2;
	size_t secondHalf = size - firstHalf;
	pairListIt center = start;
	std::advance(center, firstHalf);
	mergeSortList(start, center, firstHalf);
	mergeSortList(center, end, secondHalf);
	std::inplace_merge(start, center, end, &secondCompare);//this sorts 2 sorted halfs, meaning from start to center its sorted, and from center to end is sorted
}

void	createMainList(List *main, pairList list)
{
	for (pairListIt it = list.begin(); it != list.end(); it++)
		main->push_back(it->second);
	
	if (!list.empty())
		main->push_front(list.begin()->first);
	//first of pend will be first in main, since its always smallest
}

void	binInsertList(List *main, ListIt end, int val) {
	ListIt index = std::lower_bound(main->begin(), end, val);
	main->insert(index, val);
}

void	MergeMainAndPendList(pairList list, List *main, int addVal)
{
	size_t jcb[] = {1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845, 43691, 87381, 174763, 349525, 699051, 1398101, 2796203, 5592405, 11184811, 22369621, 44739243, 89478485, 178956971, 357913941, 715827883, 1431655765};
	int jcbIndex = 1;
	ListIt slice;
	pairListIt pairIt, lastJcbIt = list.begin();

	while (jcb[jcbIndex] <= list.size()) {
		pairIt = list.begin();
		std::advance(pairIt, jcb[jcbIndex] - 1);
		lastJcbIt = pairIt;
		int count = 0;
		while (jcb[jcbIndex] - count > jcb[jcbIndex - 1]) {
			slice = std::find(main->begin(), main->end(), pairIt->second);
			binInsertList(main, slice, pairIt->first);
			pairIt--;
			count++;
		}
		jcbIndex++;
	}
	if (jcb[jcbIndex] != list.size()) {
		pairIt = list.end();
		if (pairIt != list.begin())
			pairIt--;
		while (pairIt != lastJcbIt) {
			slice = std::find(main->begin(), main->end(), pairIt->second);
			binInsertList(main, slice, pairIt->first);
			pairIt--;
		}
	}
	if (addVal != -1)
		binInsertList(main, main->end(), addVal);

}

bool	isListSorted(List main) {
	int temp = -1;
	for (ListIt it = main.begin(); it != main.end(); it++) {
		if (temp > *it && temp != -1)
			return (std::cout << "List is unsorted......\n", false);
		temp = *it;
	}
	return (true);
}

void	printAfterList(List main)
{
	std::cout << "After:\t";
	for (ListIt it = main.begin(); it != main.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n";
}

void	PmergeMeList(char **av)
{
	pairList list;
	List main;
	int addVal = -1;

	createPairList(av, &list, &addVal);
	sortPairsList(&list);
	mergeSortList(list.begin(), list.end(), 0);
	
	createMainList(&main, list);
	MergeMainAndPendList(list, &main, addVal);

	if (!isListSorted(main))
		return ;
	// printAfterList(main);
}








//!Deque
void	createPairDeque(char **av, pairDeque *deque, int *addVal)
{
	int i = 1;

	while (av[i]) {
		if (av[i] && av[i + 1]) {
			Pair temp(std::atoi(av[i]), std::atoi(av[i + 1]));
			deque->push_back(temp);
			i += 2;
		}
		else {
			*addVal = std::atoi(av[i]);
			i++;
		}
	}
}

void	sortPairsDeque(pairDeque *deque)
{
	for (pairDequeIt it = deque->begin(); it != deque->end(); it++) {
		if (it->first > it->second) {
			int temp = it->first;
			it->first = it->second;
			it->second = temp;
		}
	}
}

void	mergeSortDeque(pairDequeIt start, pairDequeIt end, size_t size)
{
	if (size == 0 && start != end)
		size = std::distance(start, end);
	if (size <= 1)
		return ;
	size_t firstHalf = size / 2;
	size_t secondHalf = size - firstHalf;
	pairDequeIt center = start;
	std::advance(center, firstHalf);
	mergeSortDeque(start, center, firstHalf);
	mergeSortDeque(center, end, secondHalf);
	std::inplace_merge(start, center, end, &secondCompare);
}

void	createMainDeque(Deque *main, pairDeque deque)
{
	for (pairDequeIt it = deque.begin(); it != deque.end(); it++)
		main->push_back(it->second);
	
	if (!deque.empty())
		main->push_front(deque.begin()->first);
}

void	binInsertDeque(Deque *main, DequeIt end, int val) {
	DequeIt index = std::lower_bound(main->begin(), end, val);
	main->insert(index, val);
}

void	MergeMainAndPendDeque(pairDeque deque, Deque *main, int addVal)
{
	size_t jcb[] = {1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845, 43691, 87381, 174763, 349525, 699051, 1398101, 2796203, 5592405, 11184811, 22369621, 44739243, 89478485, 178956971, 357913941, 715827883, 1431655765};
	int jcbIndex = 1;
	DequeIt slice;
	pairDequeIt pairIt, lastJcbIt = deque.begin();

	while (jcb[jcbIndex] <= deque.size()) {
		pairIt = deque.begin();
		std::advance(pairIt, jcb[jcbIndex] - 1);
		lastJcbIt = pairIt;
		int count = 0;
		while (jcb[jcbIndex] - count > jcb[jcbIndex - 1]) {
			slice = std::find(main->begin(), main->end(), pairIt->second);
			binInsertDeque(main, slice, pairIt->first);
			pairIt--;
			count++;
		}
		jcbIndex++;
	}
	if (jcb[jcbIndex] != deque.size()) {
		pairIt = deque.end();
		if (pairIt != deque.begin())
			pairIt--;
		while (pairIt != lastJcbIt) {
			slice = std::find(main->begin(), main->end(), pairIt->second);
			binInsertDeque(main, slice, pairIt->first);
			pairIt--;
		}
	}
	if (addVal != -1)
		binInsertDeque(main, main->end(), addVal);

}

bool	isDequeSorted(Deque main) {
	int temp = -1;
	for (DequeIt it = main.begin(); it != main.end(); it++) {
		if (temp > *it && temp != -1)
			return (std::cout << "Deque is unsorted......\n", false);
		temp = *it;
	}
	return (true);
}

void	printAfterDeque(Deque main)
{
	std::cout << "After:\t";
	for (DequeIt it = main.begin(); it != main.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n";
}

void	PmergeMeDeque(char **av)
{
	clock_t start = clock();
	pairDeque deque;
	Deque main;
	int addVal = -1;

	createPairDeque(av, &deque, &addVal);
	sortPairsDeque(&deque);
	mergeSortDeque(deque.begin(), deque.end(), 0);
	
	createMainDeque(&main, deque);
	MergeMainAndPendDeque(deque, &main, addVal);

	if (!isDequeSorted(main))
		return ;
	printAfterDeque(main);
}
