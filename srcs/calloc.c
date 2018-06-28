/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 19:44:26 by curquiza          #+#    #+#             */
/*   Updated: 2018/06/28 19:44:29 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dyn_alloc.h"

static void	ft_bzero(void *s, size_t n)
{
	unsigned char	*s2;

	s2 = (unsigned char *)s;
	while (n--)
	{
		*s2 = 0;
		s2++;
	}
}

void		*calloc(size_t count, size_t size)
{
	void	*alloc;

	env_var_initialization();
	g_zone.histo ? calloc_input_debug(count, size) : 0;
	g_zone.histo ? calloc_call_debug() : 0;
	alloc = malloc(count * size);
	if (alloc)
		ft_bzero(alloc, count * size);
	return (alloc);
}
