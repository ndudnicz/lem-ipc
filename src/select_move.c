#include "board.h"
#include "turn.h"

static t_s32	fill_m(
t_player *const p,
t_board *const board,
t_s32 *const m
)
{
	m[0] = p->prev_y != p->y - 1 && can_go_up(p, board) && board->b[p->y - 1][p->x].team < 0;
	m[1] = p->prev_y != p->y + 1 && can_go_down(p, board) && board->b[p->y + 1][p->x].team < 0;
	m[2] = p->prev_x != p->x - 1 && can_go_left(p, board) && board->b[p->y][p->x - 1].team < 0;
	m[3] = p->prev_x != p->x + 1 && can_go_right(p, board) && board->b[p->y][p->x + 1].team < 0;
	return (0);
}

static t_s32	ft_abs(
t_s32 n
)
{
return (n >= 0 ? n : -n);
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
}

// static t_s32	get_min(
// t_s32 const *array,
// t_s32 const len
// )
// {
// 	t_s32	i;
// 	t_s32	tmp;
//
// 	i = 0;
// 	tmp = array[0];
// 	while(i < len)
// 	{
// 		if (array[i] > 0 && array[i] < tmp)
// 		{
// 			tmp = i;
// 		}
// 		i++;
// 	}
// 	return (tmp);
// }
//
// static t_s32	target_reached(
// t_s32 const px,
// t_s32 const py,
// t_target_coord *const tcoords
// )
// {
// 	if (px + 1 == tcoords->x)
// 		return (1);
// 	else if (px - 1 == tcoords->x)
// 		return (1);
// 	else if (py + 1 == tcoords->y)
// 		return (1);
// 	else if (py - 1 == tcoords->y)
// 		return (1);
// 	else
// 		return (0);
// }
//
// t_s32			r_select_move(
// t_s32 const px,
// t_s32 const py,
// t_target_coord *const tcoords,
// t_s32 const len
// )
// {
// 	t_s32	n;
// 	t_s32	tmp[4];
//
// 	printf("px: %d, py: %d\n", px, py);
// 	n = 0;
// 	if (len > 10 || px < 0 || px >= BOARD_SIZE || py < 0 || py >= BOARD_SIZE)
// 	{
// 		return (0);
// 	}
// 	else if (target_reached(px, py, tcoords))
// 	{
// 		return (1);
// 	}
// 	else
// 	{
// 		tmp[0] = r_select_move(px + 1, py, tcoords, len + 1);
// 		tmp[1] = r_select_move(px - 1, py, tcoords, len + 1);
// 		tmp[2] = r_select_move(px, py + 1, tcoords, len + 1);
// 		tmp[3] = r_select_move(px, py - 1, tcoords, len + 1);
// 		return (get_min((t_s32*)tmp, 4));
// 	}
// }
//
// t_s32	select_move(
// t_player *const p,
// t_board *const board,
// t_target_coord *const tcoords
// )
// {
// 	t_s32 const	dx = tcoords->x - p->x;
// 	t_s32 const	dy = tcoords->y - p->y;
// 	t_s32		m[4];
// 	t_s32		best;
//
// 	if (dx > 0 && can_go_right(p, board))
// 	{
// 		m[3] = r_select_move(p->x + 1, p->y, tcoords, 0);
// 		m[2] = -1;
// 	}
// 	else
// 	{
// 		m[2] = r_select_move(p->x - 1, p->y, tcoords, 0);
// 		m[3] = -1;
// 	}
// 	if (dy > 0 && can_go_down(p, board))
// 	{
// 		m[1] = r_select_move(p->x, p->y + 1, tcoords, 0);
// 		m[0] = -1;
// 	}
// 	else
// 	{
// 		m[0] = r_select_move(p->x, p->y - 1, tcoords, 0);
// 		m[1] = -1;
// 	}
// 	return (get_min((t_s32*)m, 4));
// }
