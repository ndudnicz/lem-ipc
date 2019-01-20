/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 15:29:14 by ndudnicz          #+#    #+#             */
/*   Updated: 2019/01/18 15:29:16 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "board.h"
#include "turn.h"

static	t_move moves[4] = {
	&move_up,
	&move_down,
	&move_left,
	&move_right
};

t_s32	move_up(
t_player *const p,
t_board *const board
)
{
	board->b[p->y][p->x].team = -1;
	board->b[p->y][p->x].opt = 0;
	board->b[p->y][p->x].pid = 0;
	p->y--;
	board->b[p->y][p->x].team = p->team;
	board->b[p->y][p->x].opt = p->opt;
	board->b[p->y][p->x].pid = getpid();
	return (0);
}

t_s32	move_down(
t_player *const p,
t_board *const board
)
{
	board->b[p->y][p->x].team = -1;
	board->b[p->y][p->x].opt = 0;
	board->b[p->y][p->x].pid = 0;
	p->y++;
	board->b[p->y][p->x].team = p->team;
	board->b[p->y][p->x].opt = p->opt;
	board->b[p->y][p->x].pid = getpid();
	return (0);
}

t_s32	move_left(
t_player *const p,
t_board *const board
)
{
	board->b[p->y][p->x].team = -1;
	board->b[p->y][p->x].opt = 0;
	board->b[p->y][p->x].pid = 0;
	p->x--;
	board->b[p->y][p->x].team = p->team;
	board->b[p->y][p->x].opt = p->opt;
	board->b[p->y][p->x].pid = getpid();
	return (0);
}

t_s32	move_right(
t_player *const p,
t_board *const board
)
{
	board->b[p->y][p->x].team = -1;
	board->b[p->y][p->x].opt = 0;
	board->b[p->y][p->x].pid = 0;
	p->x++;
	board->b[p->y][p->x].team = p->team;
	board->b[p->y][p->x].opt = p->opt;
	board->b[p->y][p->x].pid = getpid();
	return (0);
}

t_s32	do_move(
t_player *const p,
t_board *const board,
t_target_coord *const tcoords
)
{
	t_s32 const	move = select_move(p, board, tcoords);

	puts("do_move()"); // DEBUG
	printf("target: {x: %d, y: %d}\n", tcoords->x, tcoords->y); // DEBUG
	if (move >= 0)
	{
		moves[move](p, board);
	}
	return (0);
}
