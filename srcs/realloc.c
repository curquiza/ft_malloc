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
		// getenv(DEBUG_ENV_VAR) ? realloc_free_debug(block) : 0;
		g_zone.debug ? realloc_free_debug(block) : 0;
		free_on(block);
	}
	// getenv(DEBUG_ENV_VAR) ? realloc_call_debug() : 0;
	g_zone.debug ? realloc_call_debug() : 0;
	new = malloc(size);
	new = (t_block *)((char *)new - sizeof_header());
	if (new != block)
		ft_memcpy((char *)new + sizeof_header(), tmp_data, tmp_size);
	if (tmp_type == LARGE)
	{
		// getenv(DEBUG_ENV_VAR) ? realloc_free_debug(block) : 0;
		g_zone.debug ? realloc_free_debug(block) : 0;
		free_on(block);
	}
	return (new);
}

void	*realloc(void *ptr, size_t size)
{
	size_t		new_size;
	t_block		*b;
	t_block		*new_b;

	g_zone.debug = "1";
	// getenv(DEBUG_ENV_VAR) ? realloc_input_debug(ptr, size) : 0;
	g_zone.debug ? realloc_input_debug(ptr, size) : 0;
	if (!ptr)
	{
		// getenv(DEBUG_ENV_VAR) ? realloc_call_debug() : 0;
		g_zone.debug ? realloc_call_debug() : 0;
		return (malloc(size));
	}
	b = find_block(ptr);
	if (!b)
	{
		ft_putstr_fd("Fatal error : impossible to realloc this address.\n", 2); // debug
		return (NULL);
	}
	new_size = get_aligned_size(size, 16);
	if (b->size >= new_size)
	{
		// getenv(DEBUG_ENV_VAR) ? realloc_enough_space_debug() : 0;
		g_zone.debug ? realloc_enough_space_debug() : 0;
		return (ptr);
	}
	new_b = manage_reallocation(b, new_size);
	return ((char *)new_b + sizeof_header());
}
