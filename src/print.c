/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 16:13:54 by ndudnicz          #+#    #+#             */
/*   Updated: 2019/01/11 16:13:55 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "config.h"
#include "board.h"
#include "mystdint.h"

t_s32	print_board(
t_board *board
)
{
	t_s32	y;
	t_s32	x;

	y = 0;
	while (y < BOARD_SIZE)
	{
		x = 0;
		while (x < BOARD_SIZE)
		{
			ft_putchar((board->b[y][x] % 10) + 48);
			x++;
		}
		ft_putchar('\n');
		y++;
	}
	return (0);
}
