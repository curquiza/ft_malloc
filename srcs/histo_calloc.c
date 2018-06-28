/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   histo_calloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 19:47:28 by curquiza          #+#    #+#             */
/*   Updated: 2018/06/28 19:47:29 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dyn_alloc.h"

void	calloc_input_debug(size_t count, size_t size)
{
	ft_putstr_fd("CALLOC", 2);
	ft_putstr_fd("\t\tinput count : ", 2);
	ft_putnbr_fd(count, 2);
	ft_putstr_fd(" - input size : ", 2);
	ft_putnbr_fd(size, 2);
	ft_putstr_fd("\n", 2);
}

void	calloc_call_debug(void)
{
	ft_putstr_fd("  >> in calloc : ", 2);
}
