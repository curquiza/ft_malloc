#include "dyn_alloc.h"

void	show_alloc_mem(void)
{
	if (g_zone.tiny == NULL)
		ft_putendl("NULL");
	else
		ft_putendl("pas NULL");
}