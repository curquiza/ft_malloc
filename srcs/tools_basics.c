#include "dyn_alloc.h"

int		sizeof_header(void)
{
	return (sizeof(t_block));
}

int		page_size(void)
{
	return (getpagesize());
}