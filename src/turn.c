/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 15:28:50 by ndudnicz          #+#    #+#             */
/*   Updated: 2019/01/18 15:28:51 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mystdint.h"
#include "board.h"
#include "msg.h"
#include "turn.h"
#include "print.h"

static t_s32	find_target(
pid_t const target,
t_board *const board,
t_target_coord *const tcoords
)
{
	t_s32	y;
	t_s32	x;

	puts("find_target()");
	y = 0;
	if (target == 0)
	{
		return (-1);
	}
	while (y < BOARD_SIZE)
	{
		x = 0;
		while (x < BOARD_SIZE)
		{
			if (board->b[y][x].pid == target)
			{
				tcoords->x = x;
				tcoords->y = y;
				return (0);
			}
			x++;
		}
		y++;
	}
	puts("no target");
	return (-1);
}

static t_s32	find_an_enemy(
t_player *const p,
t_board *const board,
pid_t *target,
t_target_coord *const tcoords
)
{
	t_s32	y;
	t_s32	x;

	puts("find_an_enemy()");
	y = 0;
	while (y < BOARD_SIZE)
	{
		x = 0;
		while (x < BOARD_SIZE)
		{
			if (board->b[y][x].team >= 0 && board->b[y][x].team != p->team)
			{
				tcoords->x = x;
				tcoords->y = y;
				*target = board->b[y][x].pid;
				return (0);
			}
			x++;
		}
		y++;
	}
	puts("no ennemy");
	return (-1);
}

t_s32			do_turn(
t_player *const p,
t_board *const board
)
{
	t_msg			msg;
	pid_t			target;
	t_target_coord	tcoords;

	if (msg_rcv(p, &msg) < 0 || unforge_msg(&msg, &target) < 0)
	{
		return (0);
	}
	else
	{
		board->n_player += p->opt & P_OPT_NEW ? 1 : 0;
		p->opt &= (0xff ^ P_OPT_NEW);
		if (!(board->opt & B_OPT_PRINTER))
		{
			(void)set_printer(p, board);
		}
		if (find_target(target, board, &tcoords) < 0 &&
		find_an_enemy(p, board, &target, &tcoords) < 0)
		{
			return (0);
		}
		printf("target pid: %d\n", target);
		(void)do_move(p, board, &tcoords);
		return (0);
	}
}
