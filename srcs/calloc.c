#include "dyn_alloc.h"

static void	ft_bzero(void *s, size_t n)
{
	unsigned char	*s2;

	s2 = (unsigned char *)s;
	while (n--)
	{
		*s2 = 0;
		s2++;
	}
}

void		*calloc(size_t count, size_t size)
{
	void	*alloc;

	alloc = malloc(count * size);
	if (alloc)
		ft_bzero(alloc, count * size);
	return (alloc);
}
