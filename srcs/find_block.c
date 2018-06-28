/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 19:45:15 by curquiza          #+#    #+#             */
/*   Updated: 2018/06/28 19:45:23 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_block			*find_block(void *ptr)
{
	t_block		*block;

	pthread_mutex_lock(&g_mutex);
	block = look_for_addr_on(g_zone.large, ptr);
	if (block == NULL)
	{
		block = look_for_addr_on(g_zone.small, ptr);
		if (block == NULL)
		{
			block = look_for_addr_on(g_zone.tiny, ptr);
			if (block == NULL)
			{
				pthread_mutex_unlock(&g_mutex);
				return (NULL);
			}
			g_zone.type = TINY;
		}
		else
			g_zone.type = SMALL;
	}
	else
		g_zone.type = LARGE;
	pthread_mutex_unlock(&g_mutex);
	return (block);
}
