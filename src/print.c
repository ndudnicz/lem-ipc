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
t_board *board
)
{
	t_s32	y;
	t_s32	x;

	y = 0;
	if (board == NULL)
	{
		return (0);
	}
	printf("pid:%d\n", getpid());//
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

t_s32	set_printer(
t_player *p,
t_board *b
)
{
	ft_putstr("set_printer\n");
	p->opt |= P_OPT_PRINTER;
	b->opt |= B_OPT_PRINTER;
	return (0);
}

t_s32	unset_printer(
t_player *p,
t_board *b
)
{
	ft_putstr("unset_printer\n");
	if (b && (b->opt & B_OPT_PRINTER))
		b->opt ^= B_OPT_PRINTER;
	if (p && (p->opt & P_OPT_PRINTER))
		p->opt ^= P_OPT_PRINTER;

	return (0);
}
