#include "dyn_alloc.h"

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

static void	recur_dispay(unsigned long long int n, char *base)
{
	if (n / 16 == 0)
		ft_putchar(base[n % 16]);
	else
	{
		recur_dispay(n / 16, LITTLE_HEXA_BASE);
		ft_putchar(base[n % 16]);
	}
}

void	ft_display_addr(unsigned long long int n)
{
	ft_putstr("0x");	
	recur_dispay(n, LITTLE_HEXA_BASE);
	ft_putchar('\n');
}

void	ft_display_addr_noendl(unsigned long long int n)
{
	ft_putstr("0x");	
	recur_dispay(n, LITTLE_HEXA_BASE);
}

void	ft_display_hex_byte(unsigned char c)
{
	char	*base;

	base = LITTLE_HEXA_BASE;
	// ft_putstr("0x");	
	ft_putchar(base[c / 16]);
	c = c / 16;
	ft_putchar(base[c % 16]);
	// ft_putchar('\n');
}