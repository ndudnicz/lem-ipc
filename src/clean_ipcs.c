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
#include "player.h"
#include "board.h"
#include "print.h"

t_s32	clean_ipcs(
t_player *p
)
{
	t_board		*board;

	puts("clean_ipcs");//
	if ((int)(board = (t_board *)shmat(p->ipcs.shmid, NULL, 0)) < 0)
	{
		exit(ft_error_ret("Error: ", FAIL_SHMAT, NULL, EXIT_FAILURE));
	}
	else
	{
		printf("p->opt:%hhx\n", p->opt); //
		if (p->opt & P_OPT_PRINTER)
		{
			unset_printer(p, board);
		}
		if (board->n_player < 2)
		{
			shmctl(p->ipcs.shmid, IPC_RMID, NULL);
			semctl(p->ipcs.semid, IPC_RMID, 0);
			msgctl(p->ipcs.msgid, IPC_RMID, 0);
			shmdt(board);
			p->sem.sem_op = 1;
			semop(p->ipcs.semid, &p->sem, 1);
		}
		return (0);
	}
}
