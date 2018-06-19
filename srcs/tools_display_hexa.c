#include "dyn_alloc.h"

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_display_addr(unsigned long long int n)
{
	if (n / 16 == 0)
	{
		ft_putstr("0x");
		ft_putchar(LITTLE_HEXA_BASE[n % 16]);
	}
	else
	{
		ft_display_addr(n / 16);
		ft_putchar(LITTLE_HEXA_BASE[n % 16]);
	}
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