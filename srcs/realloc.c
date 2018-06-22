#include "dyn_alloc.h"

static t_block	*manage_reallocation(t_block *block, size_t size)
{
	t_block		*new;
	size_t		tmp_size;
	char *		tmp_data;

	tmp_size = block->size;
	tmp_data = (char *)block + sizeof_header();
	if (g_zone.type != LARGE)
		free_on(block);
	new = malloc(size);
	new = (t_block *)((char *)new - sizeof_header());
	if (new != block)
		ft_memcpy((char *)new + sizeof_header(), tmp_data, tmp_size);
	if (g_zone.type == LARGE)
		free_on(block);
	return (new);
}

void	*realloc(void *ptr, size_t size)
{
	size_t		new_size;
	t_block		*b;
	t_block		*new_b;

	ft_putendl(B_YELLOW"REALLOC"DEF); // debug
	if (!ptr)
		return (malloc(size));
	b = find_block(ptr);
	if (!b)
	{
		// ft_putendl("Fatal error : impossible to realloc this address.");
		// abort();
		return (NULL);
	}
	new_size = get_aligned_size(size, 16);
	if (b->size >= new_size)
		return (ptr);
	new_b = manage_reallocation(b, new_size);	
	return ((char *)new_b + sizeof_header());
}
