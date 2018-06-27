#include "dyn_alloc.h"

size_t	get_aligned_size(size_t size, int multiple)
{
	if (size == 0)
		return (multiple);
	return ((size - 1) / multiple * multiple + multiple);
	// return ((((size - 1) >> 4) << 4) + 16);
}

int		sizeof_header(void)
{
	return (get_aligned_size(sizeof(t_block), 16));
}

int		page_size(void)
{
	return (getpagesize());
}

void	init_debug(void)
{
	g_zone.debug = 1;
	g_zone.show_alloc_mem = 1;
}
