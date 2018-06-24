#include "dyn_alloc.h"

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

static void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
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

static void		ft_putnbr_fd(int n, int fd)
{
	if (n / 10 == 0 && n % 10 < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd(-1 * (n % 10) + '0', fd);
	}
	else if (n / 10 == 0)
		ft_putchar_fd(n % 10 + '0', fd);
	else
	{
		ft_putnbr(n / 10);
		if (n < 0)
			ft_putchar_fd(-1 * (n % 10) + '0', fd);
		else
			ft_putchar_fd(n % 10 + '0', fd);
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

void		ft_putnbr2_fd(char *s, int nbr, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putnbr_fd(nbr, fd);
	ft_putstr_fd("\n", fd);
}
