#include <unistd.h>
#include <stdarg.h>

void    ft_printhex(unsigned int n, int *count)
{
    int nbr;

    if (n >= 16)
    {
        ft_printhex(n / 16, count);
        ft_printhex(n % 16, count);
    }
    else if (n < 16)
    {
        if (n <= 9)
        {
            nbr = n + '0';
            write(1, &nbr, 1);
            *count += 1;
        }
        else if (n > 9)
        {
            nbr = n - 10 + 'a';
            write(1, &nbr, 1);
            *count += 1;
        }
    }
}

void    ft_puthex(unsigned int n, int *count)
{
    if (n == 0)
    {
        write(1, "0", 1);
        *count += 1;
    }
    else
        ft_printhex(n, count);
}

void    ft_printnbr(long int n, int *count)
{
    int nbr;

    if (n > 9)
    {
        ft_printnbr(n / 10, count);
        ft_printnbr(n % 10, count);
    }
    else if (n <= 9)
    {
        nbr = n + '0';
        write(1, &nbr, 1);
        *count += 1;
    }

}

void    ft_putnbr(int n, int *count)
{
    long int nbr;

    nbr = n;
    if (nbr == 0)
    {
        write(1, "0", 1);
        *count += 1;
    }
    if (nbr < 0)
    {
        write(1, "-", 1);
        *count += 1;
        nbr *= -1;
    }
    if (nbr > 0)
        ft_printnbr(nbr, count);
}

void    ft_putstr(char *str, int *count)
{
    int i;

    if (str == NULL)
    {
        write(1, "(null)", 6);
        *count += 6;
    }
    i = 0;
    while (str[i])
    {
        write(1, &str[i], 1);
        *count += 1;
        i++;
    }
}

void    ft_format(va_list args, char c, int *count)
{
    if (c == 's')
        ft_putstr(va_arg(args, char *), count);
    else if (c == 'd')
        ft_putnbr(va_arg(args, int), count);
    else if (c == 'x')
        ft_puthex(va_arg(args, unsigned int), count);
}

int ft_printf(const char *str, ...)
{
    va_list args;
    int count;
    int i;

    count = 0;
    i = 0;
    va_start(args, str);
    while (str[i])
    {
        if (str[i] == '%')
        {
            ft_format(args, str[i + 1], &count);
            i++;
        }
        else
        {
            write(1, &str[i], 1);
        }
        i++;
    }
    va_end(args);
    return (count);
}
/*
int main(void)
{
    ft_printf("%d", -14);
    return (0);
}*/