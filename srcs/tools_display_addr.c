#include "dyn_alloc.h"

void	ft_putaddr(unsigned long long int n)
{
	if (n / 16 == 0)
	{
		ft_putstr("0x");
		ft_putchar(HEXA_BASE[n % 16]);
	}
	else
	{
		ft_putaddr(n / 16);
		ft_putchar(HEXA_BASE[n % 16]);
	}
}

void	ft_putaddr_fd(unsigned long long int n, int fd)
{
	if (n / 16 == 0)
	{
		ft_putstr_fd("0x", fd);
		ft_putchar_fd(HEXA_BASE[n % 16], fd);
	}
	else
	{
		ft_putaddr_fd(n / 16, fd);
		ft_putchar_fd(HEXA_BASE[n % 16], fd);
	}
}

void	ft_putaddr2(char *s, unsigned long long int n) // non-official
{
	ft_putstr(s);
	ft_putaddr(n);
	ft_putstr("\n");
}
