#include "board.h"

t_s32	can_go_right(
t_player *const p,
t_board *const board
)
{
	return (p->x + 1 < BOARD_SIZE && board->b[p->y][p->x + 1].team == -1);
}

t_s32	can_go_left(
t_player *const p,
t_board *const board
)
{
	return (p->x > 1 && board->b[p->y][p->x - 1].team == -1);
}

t_s32	can_go_up(
t_player *const p,
t_board *const board
)
{
	return (p->y > 1 && board->b[p->y - 1][p->x].team == -1);
}

t_s32	can_go_down(
t_player *const p,
t_board *const board
)
{
	return (p->y + 1 < BOARD_SIZE && board->b[p->y + 1][p->x].team == -1);
}
