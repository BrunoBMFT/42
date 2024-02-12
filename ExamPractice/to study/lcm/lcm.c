//#include <stdio.h>

unsigned int	lcm(unsigned int a, unsigned int b)
{
	unsigned int lowest;

	if (!a || !b)
		return (0);
	
	if (a > b)
		lowest = a;
	else
		lowest = b;
	while (1)
	{
		if (lowest % a == 0 && lowest % b == 0)
			return (lowest);
		lowest++;
	}
	

	return (lowest);
}

/*int main(void)
{
	printf("%u", lcm(4, 6));
}*/