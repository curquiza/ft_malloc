/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 20:01:37 by curquiza          #+#    #+#             */
/*   Updated: 2018/06/28 20:02:21 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dyn_alloc.h"

pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;

static t_block	*split_block(t_block *block, size_t size)
{
	t_block		*new_block;
	t_block		*right;
	size_t		total_size;

	right = block->next;
	total_size = block->size + sizeof_header();
	new_block = (t_block *)((char *)block + sizeof_header() + size);
	new_block->size = total_size - size - sizeof_header() * 2;
	new_block->status = FREE;
	new_block->prev = block;
	new_block->next = block->next;
	block->size = size;
	block->next = new_block;
	if (right)
		right->prev = new_block;
	return (block);
}

static void		allocate_block(t_block *block, size_t size)
{
	if (g_zone.type != LARGE && block->size > size + sizeof_header())
		split_block(block, size);
	block->status = ALLOC;
}

static void		zone_type_initialization(size_t size)
{
	if (size <= TINY_MAX)
	{
		g_zone.type = TINY;
		g_zone.current = &g_zone.tiny;
	}
	else if (size <= SMALL_MAX)
	{
		g_zone.type = SMALL;
		g_zone.current = &g_zone.small;
	}
	else
	{
		g_zone.type = LARGE;
		g_zone.current = &g_zone.large;
	}
}

void			*malloc(size_t size)
{
	t_block		*alloc_b;
	size_t		new_size;

	env_var_initialization();
	if ((int)size < 0)
		return (NULL);
	pthread_mutex_lock(&g_mutex);
	new_size = get_aligned_size(size, 16);
	zone_type_initialization(new_size);
	g_zone.histo ? malloc_input_debug(size, new_size) : 0;
	alloc_b = find_or_extend(g_zone.current, new_size);
	if (!alloc_b)
		return (NULL);
	allocate_block(alloc_b, new_size);
	pthread_mutex_unlock(&g_mutex);
	g_zone.histo ? malloc_output_debug(alloc_b) : 0;
	return ((char *)alloc_b + sizeof_header());
}
