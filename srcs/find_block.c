#include "dyn_alloc.h"

static t_block	*look_for_addr_on(t_block *blocks, void *ptr)
{
	while (blocks)
	{
		if ((unsigned char *)blocks + sizeof_header() == (unsigned char *)ptr)
			return (blocks);
		blocks = blocks->next;
	}
	return (NULL);
}

t_block	*find_block(void *ptr)
{
	t_block		*block;

	block = look_for_addr_on(g_zone.large, ptr);
	if (block == NULL)
	{
		block = look_for_addr_on(g_zone.small, ptr);
		if (block == NULL)
		{
			block = look_for_addr_on(g_zone.tiny, ptr);
			if (block == NULL)
				return (NULL);
			g_zone.type = TINY;
		}
		else
			g_zone.type = SMALL;
	}
	else
		g_zone.type = LARGE;
	return (block);
}
