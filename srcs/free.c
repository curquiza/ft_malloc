#include "dyn_alloc.h"

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
		ft_putendl("Fatal error : impossible to free this address.");
		// abort();
		return ;
	}
	free_on(b_to_free);
}
