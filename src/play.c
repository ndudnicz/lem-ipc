/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 18:14:57 by ndudnicz          #+#    #+#             */
/*   Updated: 2019/01/10 18:14:59 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "board.h"
#include "libftasm.h"
#include "libft.h"
#include "mylimits.h"
#include "check_sides.h"
#include "libftasm.h"
#include "print.h"
#include "turn.h"
#include "clean_board.h"
#include "win.h"
#include "sem_manipulation.h"
#include "error.h"

static t_s32	init_h(
t_u8 *const h,
t_s32 *const sides
)
{
	h[sides[0]] = 0;
	h[sides[1]] = 0;
	h[sides[2]] = 0;
	h[sides[3]] = 0;
	h[sides[0]]++;
	h[sides[1]]++;
	h[sides[2]]++;
	h[sides[3]]++;
	return (0);
}

static t_s32	am_i_dead(
t_player *const p,
t_board *const board
)
{
	t_u8		h[USHORTMAX + 1];
	t_s32 const	sides[4] = {
		check_left(p, board),
		check_right(p, board),
		check_up(p, board),
		check_down(p, board)
	};

	(void)init_h((t_u8*)h, (t_s32*)sides);
	if (board->b[p->y][p->x].opt & B_OPT_DEAD)
		return (1);
	else if (sides[0] < USHORTMAX && p->team != sides[0] && h[sides[0]] > 1)
		return (1);
	else if (sides[1] < USHORTMAX && p->team != sides[1] && h[sides[1]] > 1)
		return (1);
	else if (sides[2] < USHORTMAX && p->team != sides[2] && h[sides[2]] > 1)
		return (1);
	else if (sides[3] < USHORTMAX && p->team != sides[3] && h[sides[3]] > 1)
		return (1);
	else
		return (0);
}

t_s32			lets_play(
t_player *const p,
t_board *board
)
{
	while (1)
	{
		lock_sem(p, 1);
		if ((int)(board = (t_board*)shmat(p->ipcs.shmid, NULL, 0)) < 0)
			exit(ft_error_ret("Error: ", FAIL_SHMAT, NULL, EXIT_FAILURE));
		else
		{
			(void)print_board(board);
			if (am_i_dead(p, board) && erase_player(getpid(), p, board) == 0 &&
			player_suicide(p, board) == 0)
			{
				ft_putendl("I AM DEAD");
				return (release_sem(p, &board));
			}
			else
			{
				if (board->opt & B_OPT_END)
					return (release_sem(p, &board) || i_win(p, board));
				(void)do_turn(p, board);
				(void)release_sem(p, &board);
			}
			usleep(TURN_WAIT);
		}
	}
	return (0);
}
