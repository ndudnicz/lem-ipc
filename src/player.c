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
#include "debug.h"//

t_s32	player_suicide(
t_player *p,
t_board *board
)
{
	puts("player_suicide()");
	if (board == NULL)
	{
		puts("A");
		ft_memset(&p->sem, 0, sizeof(struct sembuf));
		puts("B");
		p->sem.sem_op = -1;
		puts("C");
		semop(p->ipcs.semid, &p->sem, 1);
		puts("D");
		if ((int)(board = (t_board *)shmat(p->ipcs.shmid, NULL, 0)) < 0)
			exit(ft_error_ret("Error: ", FAIL_SHMAT, NULL, EXIT_FAILURE));
		else
		{
			puts("E");
			board->n_player -= board->n_player > 0 ? 1 : 0;
			puts("F");
			print_debug(p, board);
			puts("G");
			shmdt(board);
			puts("H");
			board = NULL;
			puts("I");
			p->sem.sem_op = 1;
			puts("J");
			semop(p->ipcs.semid, &p->sem, 1);
			puts("K");
		}
	}
	else
	{
		puts("L");
		board->n_player -= board->n_player > 0 ? 1 : 0;
		puts("M");
	}
	return (0);
}

t_s32	spawn_on_board(
t_player *p
)
{
	t_board *board;

	p->x = (t_u16)(arc4random() % BOARD_SIZE);
	p->y = (t_u16)(arc4random() % BOARD_SIZE);
	ft_memset(&p->sem, 0, sizeof(struct sembuf));
	p->sem.sem_op = -1;
	semop(p->ipcs.semid, &p->sem, 1);
	if ((int)(board = (t_board *)shmat(p->ipcs.shmid, NULL, 0)) < 0)
		exit(ft_error_ret("Error: ", FAIL_SHMAT, NULL, EXIT_FAILURE));
	else
	{
		board->b[p->y][p->x].team = p->team;
		board->b[p->y][p->x].pid = getpid();
		board->b[p->y][p->x].opt = p->opt;
		shmdt(board);
		p->sem.sem_op = 1;
		semop(p->ipcs.semid, &p->sem, 1);
		usleep(TURN_WAIT);
		return (0);
	}
	return (0);
}
