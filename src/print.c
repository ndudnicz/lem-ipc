/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 16:13:54 by ndudnicz          #+#    #+#             */
/*   Updated: 2019/01/11 16:13:55 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "config.h"
#include "board.h"
#include "mystdint.h"
#include "libftasm.h"
#include "board.h"

t_s32	print_board(
t_board *board
)
{
	t_s32	y;
	t_s32	x;

	y = 0;
	if (board == NULL)
	{
		return (0);
	}
	while (y < BOARD_SIZE)
	{
		x = 0;
		while (x < BOARD_SIZE)
		{
			if (board->b[y][x] == -1)
				ft_putchar('-');
			else
				ft_putchar((board->b[y][x] % 10) + 48);
			x++;
		}
		ft_putchar('\n');
		y++;
	}
	ft_putchar('\n');
	return (0);
}

t_s32	set_printer(
t_player *p,
t_board *b
)
{
	p->opt |= P_OPT_PRINTER;
	b->opt |= B_OPT_PRINTER;
	return (0);
}

t_s32	unset_printer(
t_player *p,
t_board *b
)
{
	ft_memset(&p->sem, 0, sizeof(p->sem));
	p->sem.sem_op = -1;
	semop(p->ipcs.semid, &p->sem, 1);
	if ((int)(b = (t_board *)shmat(p->ipcs.shmid, NULL, 0)) < 0)
		exit(ft_error_ret("Error: ", FAIL_SHMAT, NULL, EXIT_FAILURE));
	else
	{
		b->opt ^= B_OPT_PRINTER;
		shmdt(b);
		p->sem.sem_op = 1;
		semop(p->ipcs.semid, &p->sem, 1);
	}
	return (0);
}
