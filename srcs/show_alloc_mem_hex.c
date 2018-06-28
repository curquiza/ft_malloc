/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_hex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 19:50:06 by curquiza          #+#    #+#             */
/*   Updated: 2018/06/28 19:50:29 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dyn_alloc.h"

static void	display_zone(t_block *block)
{
	int		count;

	count = 0;
	while (block)
	{
		if (block->status == ALLOC)
		{
			hex_dump((char *)block + sizeof_header(), block->size);
			count++;
		}
		block = block->next;
	}
	if (count == 0)
		ft_putstr("No allocation in this type of zone\n");
}

void		show_alloc_mem_hex(void)
{
	pthread_mutex_lock(&g_mutex);
	ft_putstr("--- TINY ------------------------------\n");
	display_zone(g_zone.tiny);
	ft_putstr("--- SMALL -----------------------------\n");
	display_zone(g_zone.small);
	ft_putstr("--- LARGE -----------------------------\n");
	display_zone(g_zone.large);
	pthread_mutex_unlock(&g_mutex);
}
