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
#include "sem_manipulation.h"
#include "win.h"

t_s32	clean_pid(
pid_t const pid,
t_board *const board
)
{
	t_s32			x;
	t_s32			y;

	y = 0;
	while (y < BOARD_SIZE)
	{
		x = 0;
		while (x < BOARD_SIZE)
		{
			if (board->b[y][x].pid == pid)
			{
				board->b[y][x].pid = 0;
				board->b[y][x].team = -1;
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
	if (board == NULL)
	{
		lock_sem(p, 1);
		if ((int)(board = (t_board *)shmat(p->ipcs.shmid, NULL, 0)) < 0)
			exit(ft_error_ret("Error: ", FAIL_SHMAT, NULL, EXIT_FAILURE));
		else
		{
			(void)clean_pid(pid, board);
			(void)this_is_the_end(board);
			(void)release_sem(p, &board);
		}
	}
	else
	{
		(void)clean_pid(pid, board);
		(void)this_is_the_end(board);
	}
	return (0);
}
