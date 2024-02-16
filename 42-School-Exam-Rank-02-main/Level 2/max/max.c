int max(int *tab, unsigned int len)
{
	if (len == 0)
		return (0);
	
	unsigned int biggest;
	unsigned int i = 0;
	
	biggest = tab[i];
	while(i < len)
	{
		if (biggest <  tab[i])
			biggest = tab[i];
		i++;
	}
	return biggest;
}
