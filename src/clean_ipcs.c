/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_ipcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 16:12:26 by ndudnicz          #+#    #+#             */
/*   Updated: 2019/01/11 16:12:28 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <stdlib.h>

#include "mylimits.h"
#include "board.h"
#include "sem_manipulation.h"

t_s32	clean_ipcs(
t_player *const p
)
{
	t_board		*board;

	lock_sem(p, 1);
	if ((int)(board = (t_board *)shmat(p->ipcs.shmid, NULL, 0)) < 0)
		exit(ft_error_ret("Error: ", FAIL_SHMAT, NULL, EXIT_FAILURE));
	else
	{
		if (board->n_player < 1)
		{
			shmctl(p->ipcs.shmid, IPC_RMID, NULL);
			semctl(p->ipcs.semid, IPC_RMID, 0);
			msgctl(p->ipcs.msgid, IPC_RMID, 0);
		}
		release_sem(p, &board);
		return (0);
	}
}
