/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 22:13:22 by cschoen           #+#    #+#             */
/*   Updated: 2019/08/24 20:58:40 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	del_map(char **map)
{
	int	i;

	i = -1;
	while (map[++i])
		ft_strdel(&map[i]);
	ft_strdel(map);
}

int		red_x_button(void *param)
{
	(void)param;
	exit(0);
}
