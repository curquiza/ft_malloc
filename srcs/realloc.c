/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 19:48:14 by curquiza          #+#    #+#             */
/*   Updated: 2018/06/28 19:48:23 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dyn_alloc.h"

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
	enum e_type	old_type;

	pthread_mutex_lock(&g_mutex);
	old_type = g_zone.type;
	g_zone.histo ? realloc_call_debug() : 0;
	pthread_mutex_unlock(&g_mutex);
	new = (char *)malloc(size);
	pthread_mutex_lock(&g_mutex);
	ft_memmove(new, (char *)block + sizeof_header(), block->size);
	g_zone.histo ? realloc_free_debug(block) : 0;
	g_zone.type = old_type;
	pthread_mutex_unlock(&g_mutex);
	free_on(block);
	return (new);
}

void		*realloc(void *ptr, size_t size)
{
	size_t		new_size;
	t_block		*b;

	env_var_initialization();
	if ((int)size < 0)
		return (NULL);
	g_zone.histo ? realloc_input_debug(ptr, size) : 0;
	if (!ptr)
	{
		g_zone.histo ? realloc_call_debug() : 0;
		return (malloc(size));
	}
	b = find_block(ptr);
	if (!b)
	{
		g_zone.histo ? ft_putstr_fd(IMP_TO_REALLOC_MSG, 2) : 0;
		return (NULL);
	}
	new_size = get_aligned_size(size, 16);
	if (b->size >= new_size)
	{
		g_zone.histo ? realloc_enough_space_debug() : 0;
		return (ptr);
	}
	return (manage_reallocation(b, new_size));
}
