#include "dyn_alloc.h"

// static void	*ft_memcpy(void *dst, const void *src, size_t n)
// {
// 	size_t			i;
// 	unsigned char	*dst2;
// 	unsigned char	*src2;
//
// 	dst2 = (unsigned char *)dst;
// 	src2 = (unsigned char *)src;
// 	i = 0;
// 	while (i < n)
// 	{
// 		dst2[i] = src2[i];
// 		i++;
// 	}
// 	return (dst);
// }

static void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst2;
	unsigned char	*src2;

	dst2 = (unsigned char *)dst;
	src2 = (unsigned char *)src;
	if (src < dst)
	{
		src2 = src2 + len - 1;
		dst2 = dst2 + len - 1;
		while (len--)
			*dst2-- = *src2--;
	}
	else if (src >= dst)
	{
		while (len--)
			*dst2++ = *src2++;
	}
	return (dst);
}

static void	*manage_reallocation(t_block *block, size_t size)
{
	char		*new;
	size_t		tmp_size;
	char 		*tmp_data;
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
	new = (char *)malloc(size);
	assert(size >= tmp_size);
	// ft_memcpy(new, tmp_data, tmp_size);
	ft_memmove(new, tmp_data, tmp_size);
	if (tmp_type == LARGE)
	{
		// getenv(DEBUG_ENV_VAR) ? realloc_free_debug(block) : 0;
		g_zone.debug ? realloc_free_debug(block) : 0;
		free_on(block);
	}
	g_zone.debug ? realloc_output_debug(new, tmp_size, size) : 0;
	if (g_zone.show_alloc_mem == 1)
	{
		ft_putstr("\n");
		show_alloc_mem();
		ft_putstr("\n");
	}
	return (new);
}

void	*realloc(void *ptr, size_t size)
{
	size_t		new_size;
	t_block		*b;

	init_debug();
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
		g_zone.debug ? ft_putstr_fd("Fatal error : impossible to realloc this address.\n", 2) : 0;
		return (NULL);
		// return (ptr);
	}
	new_size = get_aligned_size(size, 16);
	if (b->size >= new_size)
	{
		// getenv(DEBUG_ENV_VAR) ? realloc_enough_space_debug() : 0;
		g_zone.debug ? realloc_enough_space_debug(ptr, b->size, new_size) : 0;
		return (ptr);
	}
	return (manage_reallocation(b, new_size));
}
