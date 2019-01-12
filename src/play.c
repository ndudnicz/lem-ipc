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

#include <sys/sem.h>
#include <stdlib.h>
#include <unistd.h>

#include "mylimits.h"
#include "board.h"
#include "player.h"
#include "check_sides.h"
#include "mylimits.h"
#include "libftasm.h"
#include "print.h"

static t_s32	release_sem(
t_player *p,
t_board *board
)
{
	shmdt(board);
	p->sem.sem_op = 1;
	semop(p->ipcs.semid, &p->sem, 1);
	usleep(TURN_WAIT);
	return (0);
}

static t_s32	init_h(
t_u8 *h,
t_u32 *sides
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
t_player *p,
t_board *board
)
{
	t_u8		h[SHORTMAX + 1];
	t_u32 const	sides[4] = {
		check_left(p, board),
		check_right(p, board),
		check_up(p, board),
		check_down(p, board)
	};

	(void)init_h((t_u8*)h, (t_u32*)sides);
	if (sides[0] < SHORTMAX && p->team != sides[0] && h[sides[0]] > 1)
		return (1);
	else if (sides[1] < SHORTMAX && p->team != sides[1] && h[sides[1]] > 1)
		return (1);
	else if (sides[2] < SHORTMAX && p->team != sides[2] && h[sides[2]] > 1)
		return (1);
	else if (sides[3] < SHORTMAX && p->team != sides[3] && h[sides[3]] > 1)
		return (1);
	else
		return (0);
}

t_s32			lets_play(
t_player *p,
t_board *board
)
{
	while (1)
	{
		ft_memset(&p->sem, 0, sizeof(struct sembuf));
		p->sem.sem_op = -1;
		semop(p->ipcs.semid, &p->sem, 1);
		if ((int)(board = (t_board *)shmat(p->ipcs.shmid, NULL, 0)) < 0)
			exit(ft_error_ret("Error: ", FAIL_SHMAT, NULL, EXIT_FAILURE));
		else
		{
			board->n_player += p->opt & P_OPT_NEW ? 1 : 0;
			p->opt &= (0xff ^ P_OPT_NEW);
			// printf("board->opt:%hhx\n", board->opt);
			if (!(board->opt & B_OPT_PRINTER))
				(void)set_printer(p, board);
			(void)print_board(p->opt & P_OPT_PRINTER ? board : NULL);
			if (am_i_dead(p, board))
			{
				board->n_player--;
				return (release_sem(p, board));
			}
			else
				release_sem(p, board);
		}
	}
	return (0);
}
