#include "dyn_alloc.h"

static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dst2;
	unsigned char	*src2;

	dst2 = (unsigned char *)dst;
	src2 = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dst2[i] = src2[i];
		i++;
	}
	return (dst);
}

// static void		free_debug(t_block * block)
// {
// 	ft_putstr(B_GREEN"free on"DEF" - addr : "); // debug
// 	ft_putaddr((unsigned long long)block); // debug
// 	ft_putstr("\n"); // debug
// }

static t_block	*manage_reallocation(t_block *block, size_t size)
{
	t_block		*new;
	size_t		tmp_size;
	char *		tmp_data;
	enum e_type	tmp_type;

	tmp_size = block->size;
	tmp_data = (char *)block + sizeof_header();
	tmp_type = g_zone.type;
	if (tmp_type != LARGE)
	{
		// free_debug(block); // debug
		free_on(block);
	}
	new = malloc(size);
	new = (t_block *)((char *)new - sizeof_header());
	if (new != block)
		ft_memcpy((char *)new + sizeof_header(), tmp_data, tmp_size);
	if (tmp_type == LARGE)
	{
		// free_debug(block); // debug
		free_on(block);
	}
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
		// ft_putendl("Fatal error : impossible to realloc this address."); // debug
		// abort();
		return (NULL);
	}
	new_size = get_aligned_size(size, 16);
	if (b->size >= new_size)
	{
		// ft_putendl("Enough size already"); // debug
		return (ptr);
	}
	new_b = manage_reallocation(b, new_size);
	return ((char *)new_b + sizeof_header());
}
