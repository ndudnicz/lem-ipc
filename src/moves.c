#include "board.h"
#include "moves.h"

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
	return (0);
}

t_s32	move_down(
t_player *const p,
t_board *const board
)
{
	return (0);
}

t_s32	move_left(
t_player *const p,
t_board *const board
)
{
	return (0);
}

t_s32	move_right(
t_player *const p,
t_board *const board
)
{
	return (0);
}

t_s32	do_move(
t_player *const p,
t_board *const board,
t_player_coords	tcoords
)
{
	return (0);
}
