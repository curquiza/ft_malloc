/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 19:44:56 by curquiza          #+#    #+#             */
/*   Updated: 2018/06/28 19:44:58 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dyn_alloc.h"

void	env_var_initialization(void)
{
	if (g_zone.get_histo == 0)
	{
		g_zone.get_histo = 1;
		g_zone.histo = getenv(HISTO_ENV_VAR) ? 1 : 0;
	}
	if (g_zone.get_show_free == 0)
	{
		g_zone.get_show_free = 1;
		g_zone.show_free = getenv(SHOW_FREE_ENV_VAR) ? 1 : 0;
	}
}
