/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ipcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 16:13:13 by ndudnicz          #+#    #+#             */
/*   Updated: 2019/01/11 16:13:14 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>

#include "board.h"
#include "config.h"
#include "error.h"
#include "ipcs_config.h"
#include "play.h"
#include "libftasm.h"

static t_s32	fill_board(
t_board *board
)
{
	t_s32			x;
	t_s32			y;

	y = 0;
	ft_memset(board, 0, sizeof(t_board));
	while (y < BOARD_SIZE)
	{
		x = 0;
		while (x < BOARD_SIZE)
		{
			board->b[y][x] = -1;
			x++;
		}
		y++;
	}
	return (0);
}

static t_s32	init_board(
t_player *p
)
{
	t_board			*board;

	ft_memset(&p->sem, 0, sizeof(struct sembuf));
	p->sem.sem_op = -1;
	semop(p->ipcs.semid, &p->sem, 1);
	if ((int)(board = (t_board *)shmat(p->ipcs.shmid, NULL, 0)) < 0)
		exit(ft_error_ret("Error: ", FAIL_SHMAT, NULL, EXIT_FAILURE));
	else
	{
		(void)fill_board(board);
		shmdt(board);
		p->sem.sem_op = 1;
		semop(p->ipcs.semid, &p->sem, 1);
	}
	return (0);
}

t_s32			init_ipcs(
t_player *p
)
{
	t_s32 const	first = shmget(SHM_KEY, SHM_SIZE, SHM_FLAG_F);

	if ((p->ipcs.shmid = shmget(SHM_KEY, SHM_SIZE, SHM_FLAG)) < 0)
	{
		exit(ft_error_ret("Error: ", FAIL_SHMGET, NULL, EXIT_FAILURE));
	}
	else if ((p->ipcs.semid = semget(SHM_KEY, 1, SEM_FLAG)) < 0)
	{
		exit(ft_error_ret("Error: ", FAIL_SEMGET, NULL, EXIT_FAILURE));
	}
	else if ((p->ipcs.msgid = msgget(SHM_KEY, MSG_FLAG)) < 0)
	{
		exit(ft_error_ret("Error: ", FAIL_MSGGET, NULL, EXIT_FAILURE));
	}
	else
	{
		if (first != -1)
		{
			return (init_board(p));
		}
		else
		{
			return (0);
		}
	}
}
