/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_basics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 19:50:37 by curquiza          #+#    #+#             */
/*   Updated: 2018/06/28 19:50:40 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dyn_alloc.h"

size_t	get_aligned_size(size_t size, int multiple)
{
	if (size == 0)
		return (multiple);
	return ((size - 1) / multiple * multiple + multiple);
}

int		sizeof_header(void)
{
	return (get_aligned_size(sizeof(t_block), 16));
}

int		page_size(void)
{
	return (getpagesize());
}
