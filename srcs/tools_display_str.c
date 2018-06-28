/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_display_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 19:50:58 by curquiza          #+#    #+#             */
/*   Updated: 2018/06/28 19:51:29 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dyn_alloc.h"

static size_t	ft_strlen(const char *s)
{
	int		cpt;

	cpt = -1;
	while (s[++cpt])
		;
	return (cpt);
}

void			ft_putstr(char const *s)
{
	if (s)
		write(1, s, ft_strlen(s));
}

void			ft_putstr_fd(char const *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

void			ft_putendl(char const *s)
{
	if (s)
	{
		write(1, s, ft_strlen(s));
		write(1, "\n", 1);
	}
}
