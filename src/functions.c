/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 22:26:15 by cschoen           #+#    #+#             */
/*   Updated: 2019/08/22 00:24:05 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	atoi16(char *num, int char_cnt)
{
	int	digit[2];
	int	i;

	i = -1;
	while (++i < 2)
	{
		if (*num >= '0' && *num <= '9')
			digit[i] = *num - 48;
		else if (*num >= 'A' && *num <= 'F')
			digit[i] = *num - 55;
		else if (*num >= 'a' && *num <= 'f')
			digit[i] = *num - 87;
		else
			digit[i] = 0;
		char_cnt == 2 ? ++num : 0;
	}
	return (16 * digit[0] + digit[1]);
}

int	is_int(char *num)
{
	size_t	len;
	int		sign;

	sign = 1;
	if (!*num)
		return (0);
	if (*num == '-')
		sign = -1;
	if (*num == '-' || *num == '+')
		++num;
	while (*num == '0' && ft_isdigit(*(num + 1)))
		++num;
	len = ft_strlen(num);
	if (len > 10 || len == 0)
		return (0);
	if (len < 10)
		return (1);
	if (sign == 1 && (ft_strcmp(num, "2147483647") > 0))
		return (0);
	if (sign == -1 && (ft_strcmp(num, "2147483648") > 0))
		return (0);
	return (1);
}

int	is_hex(char *hex)
{
	int	i;

	i = -1;
	if (!*hex)
		return (0);
	while (++i < 6 && *(hex + i))
		if (!((*(hex + i) >= '0' && *(hex + i) <= '9') ||
				(*(hex + i) >= 'A' && *(hex + i) <= 'F') ||
				(*(hex + i) >= 'a' && *(hex + i) <= 'f')))
			return (0);
	return ((!*(hex + i) && (i == 6 || i == 3 || i == 1)) ? 1 : 0);
}

int	is_rotate(int key)
{
	return (key == A_KEY || key == W_KEY || key == D_KEY || key == S_KEY ||
			key == Q_KEY || key == E_KEY);
}

int	is_move(int key)
{
	return (key == UP || key == DOWN || key == LEFT || key == RIGHT ||
	key == EIGHT_NUM || key == TWO_NUM || key == FOUR_NUM || key == SIX_NUM);
}
