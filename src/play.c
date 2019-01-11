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

#include "mylimits.h"
#include "board.h"
#include "player.h"
#include "check_sides.h"
#include "mylimits.h"

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
	t_u8		h[USHORTMAX];
	t_u32 const	sides[4] = {
		check_left(p, board),
		check_right(p, board),
		check_up(p, board),
		check_down(p, board)
	};
	(void)init_h((t_u8*)h, (t_u32*)sides);
	if (p->team != sides[0] && h[sides[0]] > 1)
		return (1);
	else if (p->team != sides[1] && h[sides[1]] > 1)
		return (1);
	else if (p->team != sides[2] && h[sides[2]] > 1)
		return (1);
	else if (p->team != sides[3] && h[sides[3]] > 1)
		return (1);
	else
		return (0);
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
		semop(p->ipcs.semid, &sem, 1);
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
