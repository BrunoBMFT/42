#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP
# include <iostream>
# include <stack>

template <typename var>
class MutantStack : public std::stack<var>
{
	public:
		MutantStack();
		MutantStack(const MutantStack &oth);
		MutantStack &operator=(const MutantStack &oth);
		~MutantStack();

		typedef typename std::stack<var>::container_type::iterator iterator;
		typedef typename std::stack<var>::container_type::const_iterator const_iterator;
		typedef typename std::stack<var>::container_type::reverse_iterator reverse_iterator;
		typedef typename std::stack<var>::container_type::const_reverse_iterator const_reverse_iterator;

		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;
		reverse_iterator rbegin();
		reverse_iterator rend();
		const_reverse_iterator rbegin() const;
		const_reverse_iterator rend() const;
};

# include "MutantStack.tpp"

#endif



/* 


explaining
typedef typename std::stack<T>::container_type::iterator iterator;

our Mutantstack is gonna inherit from std::stack, using it as std::stack<T>

in reality, std::stack saves into std::deque. 
saying container_type tells it to use whatever it needs, such as std::deque
so in reality, its basically a		std::stack<T>::deque::iterator
but its written as					std::stack<T>::container_type::iterator

this way, when wanting to use MutantStack as iterator, 
i dont need to write 		std::stack<int>::container_type::iterator
instead, can use it as		MutantStack<int>::iterator


*/