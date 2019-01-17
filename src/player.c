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

#include "board.h"

t_s32	player_suicide(
t_player *p,
t_board *board
)
{
	if (board == NULL)
	{
		if ((int)(board = (t_board *)shmat(p->ipcs.shmid, NULL, 0)) < 0)
			exit(ft_error_ret("Error: ", FAIL_SHMAT, NULL, EXIT_FAILURE));
		else
		{
			board->n_player--;
			shmdt(board);
		}
	}
	else
	{
		board->n_player--;
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
		board->b[p->y][p->x] = p->team;
		shmdt(board);
		p->sem.sem_op = 1;
		semop(p->ipcs.semid, &p->sem, 1);
		usleep(TURN_WAIT);
		return (0);
	}
	return (0);
}
