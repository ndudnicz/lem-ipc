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
#include "release_sem.h"
#include "mystdint.h"
#include "libft.h"//

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

static t_s32	set_player_coords(
t_player *const p,
t_board *board,
t_u16 const x,
t_u16 const y
)
{
	p->x = x;
	p->y = y;
	board->b[p->y][p->x].team = p->team;
	board->b[p->y][p->x].pid = getpid();
	board->b[p->y][p->x].opt = p->opt;
	printf("set_player_coords: pid: %d {x: %hu, y: %hu}\n", getpid(), x, y);
	ft_putnbr_fd(getpid(), 2);
	ft_putchar_fd(' ', 2);
	ft_putnbr_fd(p->x, 2);
	ft_putchar_fd(' ', 2);
	ft_putnbr_fd(p->y, 2);
	ft_putchar_fd('\n', 2);
	return (0);
}

static t_s32	select_an_empty_box(
t_player *const p,
t_board *board
)
{
	t_u16	x;
	t_u16	y;

	p->x = (t_u16)(arc4random() % BOARD_SIZE);
	p->y = (t_u16)(arc4random() % BOARD_SIZE);
	y = 0;
	if (board->b[p->y][p->x].team >= 0)
	{
		while (y < BOARD_SIZE)
		{
			x = 0;
			while (x < BOARD_SIZE)
			{
				if (board->b[y][x].team < 0)
					return (set_player_coords(p, board, x, y));
				else
				{
					printf("{x: %hu, y: %hu} taken by: {pid: %d, team: %d}\n", x, y, board->b[y][x].pid, board->b[y][x].team);
					x++;
				}
			}
			y++;
		}
	}
	else
		return (set_player_coords(p, board, p->x, p->y));
	return (0);
}

t_s32	spawn_on_board(
t_player *const p
)
{
	t_board *board;

	puts("spawn_on_board()");
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
		puts("spawn_on_board() A");
		if (board->n_player < BOARD_SIZE * BOARD_SIZE)
		{
			(void)select_an_empty_box(p, board);
			(void)release_sem(p, &board);
		}
		else
		{
			(void)release_sem(p, &board);
			exit(ft_error_ret("Error: ", TOO_MANY_PLAYER, NULL, EXIT_FAILURE));
		}
		usleep(TURN_WAIT);
		return (0);
	}
	return (0);
}
