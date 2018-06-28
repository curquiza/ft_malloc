#include "dyn_alloc.h"

static size_t		ft_strlen(const char *s)
{
	int		cpt;

	cpt = -1;
	while (s[++cpt])
		;
	return (cpt);
}

void	ft_putstr(char const *s)
{
	if (s)
		write(1, s, ft_strlen(s));
}

void	ft_putstr_fd(char const *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

void	ft_putendl(char const *s)
{
	if (s)
	{
		write(1, s, ft_strlen(s));
		write(1, "\n", 1);
	}
}
