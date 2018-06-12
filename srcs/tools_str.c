#include "dyn_alloc.h"

size_t		ft_strlen(const char *s)
{
	int		cpt;

	cpt = -1;
	while (s[++cpt])
		;
	return (cpt);
}