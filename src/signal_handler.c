/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 16:14:05 by ndudnicz          #+#    #+#             */
/*   Updated: 2019/01/11 16:14:07 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "board.h"
#include "init_ipcs.h"
#include "clean_ipcs.h"
#include "sem_manipulation.h"
#include "error.h"

static t_s32	set_player_dead(
t_player *p,
t_board *board
)
{
	t_s32	x;
	t_s32	y;

	(void)lock_sem(p, 1);
	if ((int)(board = (t_board *)shmat(p->ipcs.shmid, NULL, 0)) < 0)
		exit(ft_error_ret("Error: ", FAIL_SHMAT, NULL, EXIT_FAILURE));
	else
	{
		y = 0;
		while (y < BOARD_SIZE)
		{
			x = 0;
			while (x < BOARD_SIZE)
			{
				if (board->b[y][x].pid == getpid())
					board->b[y][x].opt |= B_OPT_DEAD;
				x++;
			}
			y++;
		}
		(void)release_sem(p, &board);
	}
	return (0);
}

t_s32			signal_handler(
int sig
)
{
	t_player	p;

	(void)init_ipcs(&p);
	if (sig == SIGALRM)
	{
		(void)ctl_all(&p);
		(void)ft_error_ret("Error: ", SEMOP_TIMEOUT, NULL, EXIT_FAILURE);
	}
	(void)set_player_dead(&p, NULL);
	return (0);
}
