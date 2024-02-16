#include <unistd.h>

void ft_putnbr(int n)
{
    char	c;
    if (n >= 10)
    {
        ft_putnbr(n / 10);
        n %= 10;
    }
    if (n < 10)
    {
        c = n + '0';
        write(1, &c, 1);
    }
}

int main(int ac, char **av)
{
    int i = 0, sum = -1, toadd = 0;
    if (ac > 1)
    {
        while (av[i])
        {
            sum += 1;
            i++;
        }
        ft_putnbr(sum);
    }
    else if (ac < 2)
        write(1, "0", 1);
    write(1, "\n", 1);
}