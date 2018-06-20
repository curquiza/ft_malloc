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

static t_block	*find_block_to_free(void *ptr)
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

static void	free_on(t_block *block)
{
	t_block	*left;
	t_block	*right;

	block->status = FREE;
	if (g_zone.type == LARGE)
	{
		left = block->prev;
		if (left)
			left->next = block->next;
		right = block->next;
		if (right)
			right->prev = block->prev;
		munmap(block, block->size + sizeof_header());
	}
}

void	free(void *ptr)
{
	t_block		*b_to_free;

	ft_putstr(B_GREEN"FREE"DEF" - addr : ");
	ft_display_addr((unsigned long long)ptr);
	ft_putstr("\n");
	
	if (ptr == NULL)
		return ;
	b_to_free = find_block_to_free(ptr);
	if (!b_to_free)
	{
		ft_putendl("Fatal error : impossible to free this address.");
		abort();
	}
	free_on(b_to_free);
}
