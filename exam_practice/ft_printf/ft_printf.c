#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

void ft_putstr(char *s, int *count)
{
    if (!s)
        s = "(null)";
    while (*s)
    {
        write(1, s++, 1);
        (*count)++;
    }
}

void ft_putnbr(int n, int *count)
{
    char c;

    if (n == -2147483648)
    {
        ft_putstr("-2147483648", count);
        return;
    }
    if (n < 0)
    {
        write(1, "-", 1);
        (*count)++;
        n = -n;
    }
    if (n > 9)
        ft_putnbr(n / 10, count);
    c = (n % 10) + '0';
    write(1, &c, 1);
    (*count)++;
}

void ft_puthex(unsigned int n, int *count)
{
    char *hex = "0123456789abcdef";

    if (n >= 16)
        ft_puthex(n / 16, count);
    write(1, &hex[n % 16], 1);
    (*count)++;
}

/* You can find all this function in the manual. "man va_arg", "man 2 va_arg", "man 3 va_arg" */
int ft_printf(const char *str, ...)
{
    va_list args;
    int count = 0;

    va_start(args, str);
    while (*str)
    {
        if (*str == '%' && *(str + 1))
        {
            str++;
            if (*str == 's')
                ft_putstr(va_arg(args, char *), &count);
            else if (*str == 'd')
                ft_putnbr(va_arg(args, int), &count);
            else if (*str == 'x')
                ft_puthex(va_arg(args, unsigned int), &count);
            else
            {
                write(1, str, 1);
                count++;
            }
        }
        else
        {
            write(1, str, 1);
            count++;
        }
        str++;
    }
    va_end(args);
    return count;
}
