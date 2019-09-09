/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 14:52:48 by cschoen           #+#    #+#             */
/*   Updated: 2019/08/25 06:12:32 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	valid_line(char **word_split, int line)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (*(word_split + ++i) != NULL)
	{
		j = 0;
		if (word_split[i][j] == '-' || word_split[i][j] == '+')
			++j;
		if (word_split[i][j] < '0' || word_split[i][j] > '9')
			wrong_line_err(line, i, 0);
		while (word_split[i][++j] && word_split[i][j] != ',')
			if (word_split[i][j] < '0' || word_split[i][j] > '9')
				wrong_line_err(line, i, 0);
		if (!word_split[i][j])
			continue ;
		if (word_split[i][++j] != '0' || word_split[i][++j] != 'x' ||
			!word_split[i][++j])
			wrong_line_err(line, i, COLOR);
		if (!is_hex(*(word_split + i) + j))
			wrong_line_err(line, i, COLOR);
	}
}
