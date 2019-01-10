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

#include "mylimits.h"
#include "board.h"
#include "check_sides.h"

static t_s32	am_i_dead(
t_player *p,
t_board *board
)
{
	t_u32 const	sides[4] = {
		check_left(p, board),
		check_right(p, board),
		check_up(p, board),
		check_down(p, board)
	};

	if (sides[0] == sides[1])
		return (0);

	// TODO check sides
}

t_s32			lets_play(
	t_player *p
)
{
	struct sembuf	sem;
	t_board			*board;

	while (1)
	{
		ft_bzero(&sem);
		sem.sem_op = -1;
		semop(e->sem_id, &sem, 1);
		board = (t_board *)shmat(p->ipcs.semid, NULL, 0);
		if ((int)(board) == -1)
		{
			return (-1);
		}
		else
		{
			shmdt(board);
			sem.sem_op = 1;
			semop(p->ipcs.semid, &sem, 1);
			if (am_i_dead(p, board))
				return (0);
		}
	}
	return (0);
}
