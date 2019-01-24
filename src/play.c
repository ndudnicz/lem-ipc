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

#include "libftasm.h"
#include "libft.h"
#include "mylimits.h"
#include "board.h"
#include "check_sides.h"
#include "mylimits.h"
#include "libftasm.h"
#include "print.h"
#include "turn.h"
#include "debug.h"
#include "clean_board.h"
#include "win.h"
#include "release_sem.h"

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
	printf("sides[0]: %d, sides[1]: %d, sides[2]: %d, sides[3]: %d\n", sides[0], sides[1], sides[2], sides[3]);
	return (0);
}


static t_s32	am_i_dead(
t_player *const p,
t_board *const board
)
{
	t_u8		h[SHORTMAX + 1];
	t_s32 const	sides[4] = {
		check_left(p, board),
		check_right(p, board),
		check_up(p, board),
		check_down(p, board)
	};

	(void)init_h((t_u8*)h, (t_s32*)sides);
	if (board->b[p->y][p->x].opt & B_OPT_DEAD)
	{
		return (1);
	}
	else if (sides[0] < SHORTMAX && p->team != sides[0] && h[sides[0]] > 1)
	{
		puts("stop sides 0");
		// return (this_is_the_end(p, board));
		return (1);
	}
	else if (sides[1] < SHORTMAX && p->team != sides[1] && h[sides[1]] > 1)
	{
		puts("stop sides 1");
		// return (this_is_the_end(p, board));
		return (1);
	}
	else if (sides[2] < SHORTMAX && p->team != sides[2] && h[sides[2]] > 1)
	{
		puts("stop sides 2");
		// return (this_is_the_end(p, board));
		return (1);
	}
	else if (sides[3] < SHORTMAX && p->team != sides[3] && h[sides[3]] > 1)
	{
		puts("stop sides 3");
		// return (this_is_the_end(p, board));
		return (1);
	}
	else
	{
		return (0);
	}
}

t_s32			lets_play(
t_player *const p,
t_board *board
)
{
	struct sembuf	sem;

	while (1)
	{
		puts("a");
		ft_memset(&sem, 0, sizeof(struct sembuf));
		puts("b");
		sem.sem_op = -1;
		puts("c");
		semop(p->ipcs.semid, &sem, 1);
		puts("d");
		if ((int)(board = (t_board *)shmat(p->ipcs.shmid, NULL, 0)) < 0)
		{
			puts("lets_play() exit");
			exit(ft_error_ret("Error: ", FAIL_SHMAT, NULL, EXIT_FAILURE));

		}
		else
		{
		puts("e");
			if (am_i_dead(p, board))
			{
				(void)print_board(board);
				printf("I AM DEAD {team: %d, pid: %d}\n", p->team, getpid()); // DEBUG
				this_is_the_end(p, board);
				(void)erase_player(getpid(), p, board);
				(void)player_suicide(p, board);
				return (release_sem(p, &board));
			}
			else
			{
		puts("f");
				if (board->opt & B_OPT_END)
				{
					(void)print_board(board);
					(void)release_sem(p, &board);
					return (i_win(p, board));
				}
		puts("g");
				(void)print_board(board);
		puts("h");
				(void)do_turn(p, board);
		puts("i");
				(void)release_sem(p, &board);
		puts("j");
			}
			usleep(TURN_WAIT);
		}
	}
	return (0);
}
