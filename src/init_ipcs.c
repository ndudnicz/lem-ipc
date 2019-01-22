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
#include <stdio.h>// // DEBUG

#include "board.h"
#include "config.h"
#include "error.h"
#include "config_ipcs.h"
#include "play.h"
#include "libftasm.h"

static t_s32	fill_board(
t_board *const board
)
{
	t_s32			x;
	t_s32			y;

	y = 0;
	ft_memset(board, 0, sizeof(t_board));
	// puts("fill_board");// // DEBUG
	// printf("board->n_player:%d\n", board->n_player);// // DEBUG
	while (y < BOARD_SIZE)
	{
		x = 0;
		while (x < BOARD_SIZE)
		{
			board->b[y][x].team = -1;
			board->b[y][x].pid = 0;
			board->b[y][x].opt = 0;
			x++;
		}
		y++;
	}
	return (0);
}

static t_s32	init_board(
t_player *const p
)
{
	t_board			*board;

	ft_memset(&p->sem, 0, sizeof(p->sem));
	p->sem.sem_op = -1;
	semop(p->ipcs.semid, &p->sem, 1);
	if ((int)(board = (t_board *)shmat(p->ipcs.shmid, NULL, 0)) < 0)
		exit(ft_error_ret("Error: ", FAIL_SHMAT, NULL, EXIT_FAILURE));
	else
	{
		(void)fill_board(board);
		shmdt(board);
		board = NULL;
		p->sem.sem_op = 1;
		semop(p->ipcs.semid, &p->sem, 1);
	}
	return (0);
}

t_s32			init_ipcs(
t_player *const p
)
{
	t_s32 const	first = shmget(IPCS_KEY, SHM_SIZE, SHM_FLAG_F) == -1 ? 0 : 1;

	// puts("init_ipcs()"); // DEBUG
	if (first == 0)
	{
		if ((p->ipcs.shmid = shmget(IPCS_KEY, SHM_SIZE, SHM_PERM)) == -1)
			exit(ft_error_ret("Error: ", FAIL_SHMGET, NULL, EXIT_FAILURE));
		if ((p->ipcs.semid = semget(IPCS_KEY, 1, SEM_PERM)) == -1)
			exit(ft_error_ret("Error: ", FAIL_SEMGET, NULL, EXIT_FAILURE));
		if ((p->ipcs.msgid = msgget(IPCS_KEY, MSG_PERM)) == -1)
			exit(ft_error_ret("Error: ", FAIL_MSGGET, NULL, EXIT_FAILURE));
		return (0);
	}
	else
	{
		if ((p->ipcs.shmid = shmget(IPCS_KEY, SHM_SIZE, SHM_PERM)) == -1)
			exit(ft_error_ret("Error: ", FAIL_SHMGET, NULL, EXIT_FAILURE));
		if ((p->ipcs.semid = semget(IPCS_KEY, 1, SEM_FLAG)) == -1)
				exit(ft_error_ret("Error: ", FAIL_SEMGET, NULL, EXIT_FAILURE));
		if ((p->ipcs.msgid = msgget(IPCS_KEY, MSG_FLAG)) == -1)
				exit(ft_error_ret("Error: ", FAIL_MSGGET, NULL, EXIT_FAILURE));
		semctl(p->ipcs.semid, 0, SETVAL, 1);
		return (init_board(p));
	}
}
