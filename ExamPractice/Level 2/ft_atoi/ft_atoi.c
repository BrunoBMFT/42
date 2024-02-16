//#include <stdlib.h>
//#include <stdio.h>

int	ft_atoi(const char *str)
{
    int i = 0, result = 0, sign = 1;;
    while (str[i] == ' ' || str[i] == '\t')
        i++;
    if (str[i] == '+' || str[i] == '-')
        if (str[i++] == '-')
            sign *= -1;
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return (result * sign);
}

/*int main(void)
{
    printf("ft_atoi: %d\n\n", ft_atoi("     -132244acd34"));
    printf("atoi: %d", atoi("     -132244acd34"));
}*/