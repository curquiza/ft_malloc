/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_display_nbr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 19:50:55 by curquiza          #+#    #+#             */
/*   Updated: 2018/06/28 19:50:55 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dyn_alloc.h"

void		ft_putnbr(int n)
{
	if (n / 10 == 0 && n % 10 < 0)
	{
		ft_putchar('-');
		ft_putchar(-1 * (n % 10) + '0');
	}
	else if (n / 10 == 0)
		ft_putchar(n % 10 + '0');
	else
	{
		ft_putnbr(n / 10);
		if (n < 0)
			ft_putchar(-1 * (n % 10) + '0');
		else
			ft_putchar(n % 10 + '0');
	}
}

void		ft_putnbr_fd(int n, int fd)
{
	if (n / 10 == 0 && n % 10 < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd(-1 * (n % 10) + '0', fd);
	}
	else if (n / 10 == 0)
		ft_putchar_fd(n % 10 + '0', fd);
	else
	{
		ft_putnbr_fd(n / 10, fd);
		if (n < 0)
			ft_putchar_fd(-1 * (n % 10) + '0', fd);
		else
			ft_putchar_fd(n % 10 + '0', fd);
	}
}

void		ft_put_sizet(size_t n)
{
	if (n / 10 == 0)
		ft_putchar(n % 10 + '0');
	else
	{
		ft_put_sizet(n / 10);
		ft_putchar(n % 10 + '0');
	}
}
