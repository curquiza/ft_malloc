/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   histo_realloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 19:48:01 by curquiza          #+#    #+#             */
/*   Updated: 2018/06/28 19:48:02 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dyn_alloc.h"

void	realloc_input_debug(void *ptr, size_t size)
{
	ft_putstr_fd("REALLOC", 2);
	ft_putstr_fd("\t\tinput size : ", 2);
	ft_putnbr_fd(size, 2);
	ft_putstr_fd(" - input address : ", 2);
	ptr ? ft_putaddr_fd((unsigned long long)ptr, 2) : ft_putstr_fd("NULL", 2);
	ft_putstr_fd("\n", 2);
}

void	realloc_call_debug(void)
{
	ft_putstr_fd("  >> in realloc : ", 2);
}

void	realloc_free_debug(t_block *b)
{
	realloc_call_debug();
	free_debug((char *)b + sizeof_header());
}

void	realloc_enough_space_debug(void)
{
	realloc_call_debug();
	ft_putstr_fd("enough space\n", 2);
}
