#include "dyn_alloc.h"

static void	merge_free_blocks(t_block *b1, t_block *b2)
{
	t_block		*b2_next;

	if ((char *)b1 + sizeof_header() + b1->size == (char *)b2)
	{
		b1->size = b1->size + sizeof_header() + b2->size;
		b2_next = b2->next;
		b1->next = b2_next;
		if (b2_next)
			b2_next->prev = b1;
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
		else
			g_zone.large = NULL;
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
	if (g_zone.show_alloc_mem == 1)
	{
		ft_putstr("\n");
		show_alloc_mem();
		ft_putstr("\n");
	}
}

void	free(void *ptr)
{
	t_block		*b_to_free;

	init_debug();
	if (ptr == NULL)
		return ;
	g_zone.debug ? free_debug(ptr) : 0;
	b_to_free = find_block(ptr);
	if (!b_to_free)
	{
		g_zone.debug ? ft_putstr_fd("Fatal error : impossible to free this address.\n", 2) : 0;
		return ;
	}
	free_on(b_to_free);
}
