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
#include "clean_board.h"

static t_s32	set_player_dead(
t_player *p,
t_board *board
)
{
	t_s32	x;
	t_s32	y;

	ft_memset(&p->sem, 0, sizeof(struct sembuf));
	p->sem.sem_op = -1;
	semop(p->ipcs.semid, &p->sem, 1);
	if ((int)(board = (t_board *)shmat(p->ipcs.shmid, NULL, 0)) < 0)
	{

			puts("set_player_dead() exit");
		exit(ft_error_ret("Error: ", FAIL_SHMAT, NULL, EXIT_FAILURE));
	}
	else
	{
		board->n_player -= board->n_player > 0 ? 1 : 0;
		y = 0;
		while (y < BOARD_SIZE)
		{
			x = 0;
			while (x < BOARD_SIZE)
			{
				if (board->b[y][x].pid == getpid())
				{
					board->b[y][x].opt |= B_OPT_DEAD;
				}
				x++;
			}
			y++;
		}
		shmdt(board);
		board = NULL;
		p->sem.sem_op = 1;
		semop(p->ipcs.semid, &p->sem, 1);
	}

}

t_s32	signal_handler(
int sig
)
{
	t_player	p;

	if (sig == SIGINT)
	{
		init_ipcs(&p);
		set_player_dead(&p, NULL);
		// erase_player(getpid(), &p, NULL);
		// player_suicide(&p, NULL);
		// clean_ipcs(&p);
		// exit(EXIT_SUCCESS);
		return (0);
	}
	else
	{
		return (0);
	}
}
