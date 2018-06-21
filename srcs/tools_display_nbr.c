#include "dyn_alloc.h"

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void		ft_putnbr(int n)
{
	if (n / 10 == 0 && n % 10 < 0)
	{
		ft_putchar('-');
		ft_putchar(-1 * (n % 10) + '0');
	}
	else if (n / 10 == 0)
		ft_putchar(n % 10 + '0');
	else
	{
		ft_putnbr(n / 10);
		if (n < 0)
			ft_putchar(-1 * (n % 10) + '0');
		else
			ft_putchar(n % 10 + '0');
	}
}

void		ft_put_sizet(size_t n)
{
	if (n / 10 == 0)
		ft_putchar(n % 10 + '0');
	else
	{
		ft_put_sizet(n / 10);
		ft_putchar(n % 10 + '0');
	}
}

void		ft_putnbr2(char *s, int nbr)
{
	ft_putstr(s);
	ft_putnbr(nbr);
	ft_putstr("\n");
}
