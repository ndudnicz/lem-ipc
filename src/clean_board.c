/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_board.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 18:06:15 by ndudnicz          #+#    #+#             */
/*   Updated: 2019/01/17 18:06:17 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "libftasm.h"
#include "mystdint.h"
#include "board.h"
#include "print.h"

t_s32	clean_pid(
pid_t const pid,
t_board *const board
)
{
	t_s32			x;
	t_s32			y;

	y = 0;
	puts("clean_pid()");// // DEBUG
	while (y < BOARD_SIZE)
	{
		x = 0;
		while (x < BOARD_SIZE)
		{
			if (board->b[y][x].pid == pid)
			{
				printf("pid:%d\nteam:%d\nopt:%p\n", board->b[y][x].pid, board->b[y][x].team, board->b[y][x].opt); // DEBUG
				board->b[y][x].pid = 0;
				board->b[y][x].team = -1;
				if (board->b[y][x].opt & P_OPT_PRINTER)
					unset_printer(NULL, board);
				board->b[y][x].opt = 0;
			}
			x++;
		}
		y++;
	}
	return (0);
}

t_s32	erase_player(
pid_t const pid,
t_player *const p,
t_board *board
)
{
	puts("erase_player()");//
	if (board == NULL)
	{
		ft_memset(&p->sem, 0, sizeof(struct sembuf));
		p->sem.sem_op = -1;
		semop(p->ipcs.semid, &p->sem, 1);
		if ((int)(board = (t_board *)shmat(p->ipcs.shmid, NULL, 0)) < 0)
			exit(ft_error_ret("Error: ", FAIL_SHMAT, NULL, EXIT_FAILURE));
		else
		{
			clean_pid(pid, board);
			shmdt(board);
			// board = NULL;
			p->sem.sem_op = 1;
			semop(p->ipcs.semid, &p->sem, 1);
		}
	}
	else
	{
		clean_pid(pid, board);
	}
	return (0);
}
