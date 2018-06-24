#include "dyn_alloc.h"

void	ft_putaddr(unsigned long long int n)
{
	if (n / 16 == 0)
	{
		ft_putstr("0x");
		ft_putchar(LITTLE_HEXA_BASE[n % 16]);
	}
	else
	{
		ft_putaddr(n / 16);
		ft_putchar(LITTLE_HEXA_BASE[n % 16]);
	}
}

void	ft_putaddr_fd(unsigned long long int n, int fd)
{
	if (n / 16 == 0)
	{
		ft_putstr_fd("0x", fd);
		ft_putchar_fd(LITTLE_HEXA_BASE[n % 16], fd);
	}
	else
	{
		ft_putaddr_fd(n / 16, fd);
		ft_putchar_fd(LITTLE_HEXA_BASE[n % 16], fd);
	}
}

// void	ft_display_hex_byte(unsigned char c)
// {
// 	char	*base;
//
// 	base = LITTLE_HEXA_BASE;
// 	// ft_putstr("0x");
// 	ft_putchar(base[c / 16]);
// 	c = c / 16;
// 	ft_putchar(base[c % 16]);
// 	// ft_putchar('\n');
// }
