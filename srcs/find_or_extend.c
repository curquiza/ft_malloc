/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_or_extend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 20:02:33 by curquiza          #+#    #+#             */
/*   Updated: 2018/06/28 20:03:42 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dyn_alloc.h"

static size_t	get_extend_size(size_t size)
{
	size_t	s;

	if (g_zone.type == TINY)
		s = (TINY_MAX + sizeof_header()) * ZONE_ALLOC_NB;
	else if (g_zone.type == SMALL)
		s = (SMALL_MAX + sizeof_header()) * ZONE_ALLOC_NB;
	else
		s = size + sizeof_header();
	return (get_aligned_size(s, page_size()));
}

static t_block	*extend_heap(size_t size, t_block *previous)
{
	t_block	*b;
	size_t	mmap_size;

	mmap_size = get_extend_size(size);
	b = mmap(0, mmap_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE,
				-1, 0);
	if (b == MAP_FAILED)
		return (NULL);
	b->status = FREE;
	b->size = mmap_size - sizeof_header();
	b->next = NULL;
	b->prev = previous;
	if (previous)
		previous->next = b;
	return (b);
}

static t_block	*find_available_or_last_block(t_block *blocks, size_t size)
{
	while (blocks)
	{
		if (blocks->size >= size && blocks->status == FREE)
			return (blocks);
		if (!blocks->next)
			break ;
		blocks = blocks->next;
	}
	return (blocks);
}

static bool		is_available_block(t_block *block, size_t size)
{
	return (block->size >= size && block->status == FREE ? true : false);
}

t_block			*find_or_extend(t_block **blocks, size_t size)
{
	t_block		*place;

	if (!*blocks)
	{
		*blocks = extend_heap(size, *blocks);
		return (*blocks);
	}
	place = find_available_or_last_block(*blocks, size);
	if (is_available_block(place, size) == true)
		return (place);
	else
		return (extend_heap(size, place));
}
