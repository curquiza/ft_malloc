/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_display_addr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 19:50:43 by curquiza          #+#    #+#             */
/*   Updated: 2018/06/28 19:50:45 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dyn_alloc.h"

void	ft_putaddr(unsigned long long int n)
{
	if (n / 16 == 0)
	{
		ft_putstr("0x");
		ft_putchar(HEXA_BASE[n % 16]);
	}
	else
	{
		ft_putaddr(n / 16);
		ft_putchar(HEXA_BASE[n % 16]);
	}
}

void	ft_putaddr_fd(unsigned long long int n, int fd)
{
	if (n / 16 == 0)
	{
		ft_putstr_fd("0x", fd);
		ft_putchar_fd(HEXA_BASE[n % 16], fd);
	}
	else
	{
		ft_putaddr_fd(n / 16, fd);
		ft_putchar_fd(HEXA_BASE[n % 16], fd);
	}
}
