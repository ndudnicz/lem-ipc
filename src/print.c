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

#include <stdlib.h>
#include <unistd.h>

#include "config.h"
#include "board.h"
#include "mystdint.h"
#include "libftasm.h"
#include "board.h"

t_s32	print_board(
t_board *const board
)
{
	t_s32	y;
	t_s32	x;

	y = 0;
	if (board == NULL)
	{
		return (0);
	}
	while (y < BOARD_SIZE)
	{
		x = 0;
		while (x < BOARD_SIZE)
		{
			if (board->b[y][x].team == -1)
				ft_putchar('-');
			else
				ft_putchar((board->b[y][x].team % 10) + 48);
			x++;
		}
		ft_putchar('\n');
		y++;
	}
	return (!ft_putchar('\n'));
}
