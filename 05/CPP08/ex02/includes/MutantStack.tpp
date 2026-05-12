#include "MutantStack.hpp"

template <typename var>
MutantStack<var>::MutantStack() : std::stack<var>() {}

template <typename var>
MutantStack<var>::MutantStack(const MutantStack &oth) : std::stack<var>(oth) {}

template <typename var>
MutantStack<var> &MutantStack<var>::operator=(const MutantStack &oth) {
	if (this != &oth) {
		std::stack<var>::operator=(oth);
	}
	return (*this);
}

template <typename var>
MutantStack<var>::~MutantStack() {}


template <typename var>
typename MutantStack<var>::iterator MutantStack<var>::begin() {
	return (std::stack<var>::c.begin());
}
template <typename var>
typename MutantStack<var>::iterator MutantStack<var>::end() {
	return (std::stack<var>::c.end());
}

template <typename var>
typename MutantStack<var>::const_iterator MutantStack<var>::begin() const {
	return (std::stack<var>::c.begin());
}
template <typename var>
typename MutantStack<var>::const_iterator MutantStack<var>::end() const {
	return (std::stack<var>::c.end());
}

template <typename var>
typename MutantStack<var>::reverse_iterator MutantStack<var>::rbegin() {
	return (std::stack<var>::c.rbegin());
}
template <typename var>
typename MutantStack<var>::reverse_iterator MutantStack<var>::rend() {
	return (std::stack<var>::c.rend());
}

template <typename var>
typename MutantStack<var>::const_reverse_iterator MutantStack<var>::rbegin() const {
	return (std::stack<var>::c.rbegin());
}

template <typename var>
typename MutantStack<var>::const_reverse_iterator MutantStack<var>::rend() const {
	return (std::stack<var>::c.rend());
}
