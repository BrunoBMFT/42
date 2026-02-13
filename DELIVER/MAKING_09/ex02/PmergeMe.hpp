#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <list>
# include <deque>
// # include <string>
// # include <utility>
# include <algorithm>
// # include <climits>
// # include <ctime>


typedef std::pair<int, int> Pair;

typedef std::list<int> List;
typedef std::list<int>::iterator ListIt;
typedef std::list<std::pair<int, int> > pairList;
typedef std::list<std::pair<int, int> >::iterator pairListIt;

typedef std::deque<int> Deque;
typedef std::deque<int>::iterator DequeIt;
typedef std::deque<std::pair<int, int> > pairDeque;
typedef std::deque<std::pair<int, int> >::iterator pairDequeIt;



void	PmergeMeList(char **av);
void	PmergeMeDeque(char **av);

#endif