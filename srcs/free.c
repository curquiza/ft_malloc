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

static void	merge_free_blocks(t_block *b1, t_block *b2)
{
	if ((unsigned char *)b1 + sizeof_header() + b1->size == (unsigned char *)b2)
	{
		b1->size = b1->size + sizeof_header() + b2->size;
		b1->next = b2->next;
		b2->next = NULL;
		b2->prev = NULL;
		b2->size = 0;
	}
}

void	free_on(t_block *block)
{
	t_block	*left;
	t_block	*right;

	block->status = FREE;
	left = block->prev;
	right = block->next;
	if (g_zone.type == LARGE)
	{
		if (left)
			left->next = block->next;
		if (right)
			right->prev = block->prev;
		munmap(block, block->size + sizeof_header());
	}
	else
	{
		if (right && right->status == FREE)
			merge_free_blocks(block, right);
		if (left && left->status == FREE)
			merge_free_blocks(left, block);
	}
}

void	free(void *ptr)
{
	t_block		*b_to_free;

	ft_putstr(B_GREEN"FREE"DEF" - addr : "); // debug
	ft_display_addr((unsigned long long)ptr); // debug
	ft_putstr("\n"); // debug
	
	if (ptr == NULL)
		return ;
	b_to_free = find_block(ptr);
	if (!b_to_free)
	{
		// ft_putendl("Fatal error : impossible to free this address.");
		// abort();
		return ;
	}
	free_on(b_to_free);
}
