/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 12:32:00 by ndudnicz          #+#    #+#             */
/*   Updated: 2019/01/17 12:32:02 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "board.h"
#include "sem_manipulation.h"
#include "turn.h"
#include "error.h"

t_s32			player_suicide(
t_player *const p,
t_board *board
)
{
	if (board == NULL)
	{
		(void)lock_sem(p, IPC_NOWAIT);
		if ((int)(board = (t_board*)shmat(p->ipcs.shmid, NULL, 0)) < 0)
			exit(ft_error_ret("Error: ", FAIL_SHMAT, NULL, EXIT_FAILURE));
		else
		{
			board->n_player -= board->n_player > 0 ? 1 : 0;
			release_sem(p, &board);
		}
	}
	else
	{
		board->n_player -= board->n_player > 0 ? 1 : 0;
	}
	return (0);
}

static t_s32	set_player_coords(
t_player *const p,
t_board *board,
t_u16 const x,
t_u16 const y
)
{
	p->x = x;
	p->y = y;
	board->b[p->y][p->x].team = p->team;
	board->b[p->y][p->x].pid = getpid();
	board->b[p->y][p->x].opt = p->opt;
	return (0);
}

static t_s32	select_an_empty_box(
t_player *const p,
t_board *board
)
{
	t_u16	x;
	t_u16	y;

	p->x = (t_u16)(arc4random() % BOARD_SIZE);
	p->y = (t_u16)(arc4random() % BOARD_SIZE);
	y = 0;
	if (board->b[p->y][p->x].team >= 0)
	{
		while (y < BOARD_SIZE)
		{
			x = 0;
			while (x < BOARD_SIZE)
			{
				if (board->b[y][x].team < 0)
					return (set_player_coords(p, board, x, y));
				else
					x++;
			}
			y++;
		}
	}
	else
		return (set_player_coords(p, board, p->x, p->y));
	return (0);
}

t_s32			spawn_on_board(
t_player *const p
)
{
	t_board *board;

	lock_sem(p, 1);
	if ((int)(board = (t_board*)shmat(p->ipcs.shmid, NULL, 0)) < 0)
		exit(ft_error_ret("Error: ", FAIL_SHMAT, NULL, EXIT_FAILURE));
	else
	{
		if ((t_s32)board->n_player < BOARD_SIZE * BOARD_SIZE)
		{
			(void)select_an_empty_box(p, board);
			(void)release_sem(p, &board);
		}
		else
		{
			(void)release_sem(p, &board);
			exit(ft_error_ret("Error: ", TOO_MANY_PLAYER, NULL, EXIT_FAILURE));
		}
		usleep(TURN_WAIT);
		return (0);
	}
	return (0);
}
