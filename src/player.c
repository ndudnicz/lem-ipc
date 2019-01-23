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

#include "libftasm.h"
#include "board.h"
#include "debug.h"//

t_s32	player_suicide(
t_player *const p,
t_board *board
)
{
	// puts("player_suicide()"); // DEBUG
	if (board == NULL)
	{
		// puts("A"); // DEBUG
		ft_memset(&p->sem, 0, sizeof(struct sembuf));
		// puts("B"); // DEBUG
		p->sem.sem_op = -1;
		// puts("C"); // DEBUG
		semop(p->ipcs.semid, &p->sem, IPC_NOWAIT);
		// puts("D"); // DEBUG
		if ((int)(board = (t_board *)shmat(p->ipcs.shmid, NULL, 0)) < 0)
		{
			puts("player_suicide() exit");
			exit(ft_error_ret("Error: ", FAIL_SHMAT, NULL, EXIT_FAILURE));

		}
		else
		{
	// print_debug(p, board); // DEBUG
			// puts("E"); // DEBUG
			board->n_player -= board->n_player > 0 ? 1 : 0;
			// puts("F"); // DEBUG
			// print_debug(p, board);
			// puts("G"); // DEBUG
			shmdt(board);
			// puts("H"); // DEBUG
			board = NULL;
			// puts("I"); // DEBUG
			p->sem.sem_op = 1;
			// puts("J"); // DEBUG
			semop(p->ipcs.semid, &p->sem, 1);
			// puts("K"); // DEBUG
		}
	}
	else
	{
		// puts("E"); // DEBUG
		board->n_player -= board->n_player > 0 ? 1 : 0;
		// puts("F"); // DEBUG
	}
	return (0);
}

t_s32	spawn_on_board(
t_player *const p
)
{
	t_board *board;
// puts("spawn_on_board"); // DEBUG
	p->x = (t_u16)(arc4random() % BOARD_SIZE);
	p->y = (t_u16)(arc4random() % BOARD_SIZE);
	ft_memset(&p->sem, 0, sizeof(struct sembuf));
	p->sem.sem_op = -1;
	semop(p->ipcs.semid, &p->sem, 1);
	if ((int)(board = (t_board *)shmat(p->ipcs.shmid, NULL, 0)) < 0)
	{
		puts("spawn_on_board() exit");
		exit(ft_error_ret("Error: ", FAIL_SHMAT, NULL, EXIT_FAILURE));

	}
	else
	{
		if (board->n_player < BOARD_SIZE * BOARD_SIZE)
		{
			board->b[p->y][p->x].team = p->team;
			board->b[p->y][p->x].pid = getpid();
			// printf("board->b[p->y][p->x].pid: %d\n", board->b[p->y][p->x].pid); // DEBUG
			board->b[p->y][p->x].opt = p->opt;
		}
		else
			exit(ft_error_ret("Error: ", TOO_MANY_PLAYER, NULL, EXIT_FAILURE));
		shmdt(board);
		p->sem.sem_op = 1;
		semop(p->ipcs.semid, &p->sem, 1);
		usleep(TURN_WAIT);
		return (0);
	}
	return (0);
}
