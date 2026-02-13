/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 20:00:09 by cgodecke          #+#    #+#             */
/*   Updated: 2026/02/13 02:30:15 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	main(int argc, char **argv)
{
	if (argc < 2)
		return (std::cerr << "Not enough arguments provided\n", 1);
	
	{
		std::cout << "using std::list" << std::endl;
		clock_t start = clock();
		std::list< std::pair<int, int> > listy;
		std::list<int> main_chain;
		// For value if the amount of number is odd
		int additional_value = -1;
		
		print_before(argv);
		create_pairs(&listy, argv, &additional_value);

		sort_pairs(&listy);
		mergeSort(listy.begin(), listy.end(), 0);

		init_main_chain(&main_chain, listy);
		
		insert_into_main_chain(listy, &main_chain, additional_value);
		print_after(main_chain);
		
		clock_t end = clock();
		std::cout << "Time to process a range of " << main_chain.size() << " elements with std::list: " << static_cast<double>(end - start) / 1000 << " millisec" << std::endl << std::endl;
	}
	return (0);
}


/*
Main diffs between chosen containers:

Relevant for FJ:
- Deque: manages its elements with a dynamic array, provides random access
- List: manages its elements as a doubly linked list and does not provide random access

- Deque: provides fast insertions and deletions at both the end and the beginning. Inserting and deleting elements in the middle is relatively slow 
because all elements up to either of both ends may be moved to make room or to fill a gap.
- List: inserting and removing elements is fast at each position, including both ends

Neglible for FJ:
- Deque: Any insertion or deletion of elements other than at the beginning or end invalidates all pointers, references, and iterators that refer to elements of the deque
- List: Inserting and deleting elements does not invalidate pointers, references, and iterators to other elements.

Conclusion
The results you observed align with expectations based on the theoretical underpinnings of each container's design and the
practical implications of those designs on sorting performance. While std::list offers advantages in specific
scenarios (e.g., frequent insertions and deletions at arbitrary positions within a large dataset), std::deque is generally more
suited for operations like sorting, where its structural advantages—such as random access and better cache locality—translate into
significant performance benefits.
*/
