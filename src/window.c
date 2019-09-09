/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 23:31:17 by cschoen           #+#    #+#             */
/*   Updated: 2019/07/06 20:14:14 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char	*get_file_name(char *title)
{
	size_t	len;

	len = ft_strlen(title);
	while (len-- && *(title + len))
		if (*(title + len) == '/')
			break ;
	++len;
	return (title + len);
}

t_win		*new_window(t_fdf **fdf, int x_win, int y_win, char *title)
{
	t_win	*win;

	win = NULL;
	if (!(win = (t_win*)malloc(sizeof(t_win))))
		error("No memory allocated for new window");
	win->x_win = x_win;
	win->y_win = y_win;
	win->title = get_file_name(title);
	win->win_ptr = mlx_new_window((*fdf)->mlx_ptr, x_win, y_win, win->title);
	if (!(win->win_ptr))
		error("Failed to create a new window");
	return (win);
}
