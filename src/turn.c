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

	(void)msg_rcv(p, &msg);
	(void)unforge_msg(&msg, &target);
	board->n_player += p->opt & P_OPT_NEW ? 1 : 0;
	p->opt &= (0xff ^ P_OPT_NEW);
	if (find_target(target, board, &tcoords) < 0 &&
	find_an_enemy(p, board, &target, &tcoords) < 0)
	{
		return (0);
	}
	(void)forge_msg(&msg, p, target);
	(void)msg_send(p, &msg);
	(void)do_move(p, board, &tcoords);
	return (0);
}
