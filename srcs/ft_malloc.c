#include "dyn_alloc.h"

void	*malloc(size_t size)
{
	(void)size;
	write(1, "MALLOC\n", 7);
	return ((void *)"coco");
}