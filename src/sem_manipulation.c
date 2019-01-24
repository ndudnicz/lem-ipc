/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_manipulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 14:52:32 by ndudnicz          #+#    #+#             */
/*   Updated: 2019/01/24 14:52:33 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "board.h"
#include "libftasm.h"
#include "clean_ipcs.h"

t_s32	lock_sem(
t_player *const p,
int semflag
)
{
	alarm(SEMOP_TIMEOUT_VALUE);
	ft_memset(&p->sem, 0, sizeof(struct sembuf));
	p->sem.sem_op = -1;
	if (semop(p->ipcs.semid, &p->sem, semflag) < 0)
	{
		(void)ctl_all(p);
	}
	alarm(0);
	return (0);
}

t_s32	release_sem(
t_player *const p,
t_board **board
)
{
	shmdt(*board);
	*board = NULL;
	p->sem.sem_op = 1;
	semop(p->ipcs.semid, &p->sem, 1);
	return (0);
}
