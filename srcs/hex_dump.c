#include "dyn_alloc.h"

static void	ft_putbyte_hex(unsigned char c)
{
	ft_putchar(HEXA_BASE[c / 16]);
	ft_putchar(HEXA_BASE[c % 16]);
}

static void	write_hexa(void *addr, size_t remaining_size)
{
	size_t	i;

	i = 0;
	while (i < 16 && i < remaining_size)
	{
		ft_putbyte_hex(*((unsigned char *)addr + i));
		if (i != 15 && i != remaining_size - 1)
			ft_putchar(' ');
		i++;
	}
}

static void	write_ascii(void *addr, size_t remaining_size)
{
	size_t			i;
	unsigned char 	c;

	i = 0;
	while (i < 16 && i < remaining_size)
	{
		c = *((unsigned char *)addr + i);
		if (c >= 32 && c <= 126)
			ft_putchar(c);
		else
			ft_putchar('.');
		i++;
	}
}

static void	write_one_line(void *addr, size_t remaining_size)
{
	int		i;

	ft_putaddr((unsigned long long)addr);
	ft_putstr(": ");
	write_hexa(addr, remaining_size);
	if (remaining_size >= 16)
		i = 16 * 3 - 1;
	else
		i = (remaining_size % 16) * 3 - 1;
	while (i < 16 * 3 + 1)
	{
		ft_putchar(' ');
		i++;
	}
	write_ascii(addr, remaining_size);
	ft_putchar('\n');
}

void	hex_dump(void *addr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		write_one_line(addr + i, size - i);
		i += 16;
	}
}
