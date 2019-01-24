/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 14:57:27 by ndudnicz          #+#    #+#             */
/*   Updated: 2019/01/24 14:57:28 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "board.h"
#include "turn.h"

static t_s32	fill_m(
t_player *const p,
t_board *const board,
t_s32 *const m
)
{
	m[0] = p->prev_y != p->y - 1 && can_go_up(p, board) &&
	board->b[p->y - 1][p->x].team < 0;
	m[1] = p->prev_y != p->y + 1 && can_go_down(p, board) &&
	board->b[p->y + 1][p->x].team < 0;
	m[2] = p->prev_x != p->x - 1 && can_go_left(p, board) &&
	board->b[p->y][p->x - 1].team < 0;
	m[3] = p->prev_x != p->x + 1 && can_go_right(p, board) &&
	board->b[p->y][p->x + 1].team < 0;
	return (0);
}

static t_s32	choose_other_move(
t_s32 *m
)
{
	if (m[MOVE_RIGHT])
		return (MOVE_RIGHT);
	else if (m[MOVE_LEFT])
		return (MOVE_LEFT);
	else if (m[MOVE_UP])
		return (MOVE_UP);
	else if (m[MOVE_DOWN])
		return (MOVE_DOWN);
	else
		return (NO_MOVE);
}

t_s32			select_move(
t_player *const p,
t_board *const board,
t_target_coord *const tcoords
)
{
	t_s32 const	dx = tcoords->x - p->x;
	t_s32 const	dy = tcoords->y - p->y;
	t_s32		m[4];

	fill_m(p, board, (t_s32*)m);
	if ((dx > 0 || dy > 0) && (m[MOVE_RIGHT] || m[MOVE_DOWN]))
	{
		return (m[MOVE_RIGHT] ? MOVE_RIGHT : MOVE_DOWN);
	}
	else if ((dx > 0 || dy < 0) && (m[MOVE_RIGHT] || m[MOVE_UP]))
	{
		return (m[MOVE_RIGHT] ? MOVE_RIGHT : MOVE_UP);
	}
	else if ((dx < 0 || dy > 0) && (m[MOVE_LEFT] || m[MOVE_DOWN]))
	{
		return (m[MOVE_LEFT] ? MOVE_LEFT : MOVE_DOWN);
	}
	else if ((dx < 0 || dy < 0) && (m[MOVE_LEFT] || m[MOVE_UP]))
	{
		return (m[MOVE_LEFT] ? MOVE_LEFT : MOVE_UP);
	}
	else
	{
		return (choose_other_move((t_s32*)m));
	}
}
