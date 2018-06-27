#include "dyn_alloc.h"

size_t	get_aligned_size(size_t size, int multiple)
{
	if (size == 0)
		return (multiple);
	return ((size - 1) / multiple * multiple + multiple);
}

int		sizeof_header(void)
{
	return (get_aligned_size(sizeof(t_block), 16));
}

int		page_size(void)
{
	return (getpagesize());
}
