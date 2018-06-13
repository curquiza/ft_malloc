#include "dyn_alloc.h"

void	ft_putstr(char const *s)
{
	if (s)
		write(1, s, ft_strlen(s));
}

void	ft_putendl(char const *s)
{
	if (s)
	{
		write(1, s, ft_strlen(s));
		write(1, "\n", 1);
	}
}

void	ft_putendl2(char *s1, char *s2)
{
	ft_putstr(s1);
	ft_putstr(s2);
	write(1, "\n", 1);
}

void	ft_putstr_fd(char const *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

void	ft_putendl2_fd(char *s1, char *s2, int fd)
{
	ft_putstr_fd(s1, fd);
	ft_putstr_fd(s2, fd);
	write(fd, "\n", 1);
}