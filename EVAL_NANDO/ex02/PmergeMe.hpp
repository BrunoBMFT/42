#pragma once 

#include <list>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <sys/time.h>
#include <iomanip>
#include <deque>
/*value - "3 2 1 4 5 6 8 7" */
/*index -  0 1 2 3 4 5 6 7*/
/* 5 7 3 1 8 2 6 4 */

#ifndef TEST
#define TEST 0
#endif

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m" 
#define BLUE  "\033[34m"
#define OLIVE "\033[38;5;3m"
#define PURPLE "\033[38;5;5m"
#define ORANGE "\033[38;5;208m"
#define CYAN "\033[38;5;6m"
#define LIGHT_GRAY "\033[38;5;7m"
#define DARK_GRAY "\033[38;5;8m"
#define END  "\033[0m"


class PmergeMe
{
    private:
        std::vector<int> vt;
        std::vector<int> og_vt;

        std::deque<int> dque;
        std::deque<int> og_dq;



        timeval vt_start;
        timeval vt_end;

        timeval dq_start;
        timeval dq_end;


    public:
        typedef std::vector<std::pair<int, int> > vector_pair; 
        typedef std::vector<int>::iterator vtr_it; 
        typedef std::vector<int> vtr; 

        typedef std::deque<std::pair<int, int> > dq_pair; 
        typedef std::deque<int>::iterator dq_it; 
        typedef std::deque<int> dq; 
        
        void tester();

        PmergeMe(int ac, char **av);
        PmergeMe(const PmergeMe &o);
        PmergeMe &operator=(const PmergeMe &o);
        void fill_vt(std::string str);
        void fill_dq(std::string str);

        void pv(PmergeMe::vtr a );
        void pv(PmergeMe::dq a );

        
        void merge_insert(vtr &vetor, int cel_size);
        void merge_insert(dq &deque, int cel_size);
        

        vtr split(const std::string &str, vtr token_vector);
        dq split(const std::string &str, dq token_dq);
        
    
    ~PmergeMe();
};


