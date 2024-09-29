#include "../includes/sudoku.h"

int	main(int ac, char **av)
{
	t_map	map;

	if (!parser(ac, av, &map))
		return (1);
	init_map(&map);

 	solve(&map);
	if (av[2] && av[2] == "print")
		print_map(&map);
}
