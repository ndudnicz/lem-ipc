#include "mystdint.h"
#include "board.h"
#include "msg.h"
#include "turn.h"

static t_s32	find_target(
pid_t const target,
t_board *const board,
t_player_coords *const tcoords
)
{
	t_s32	y;
	t_s32	x;

	y = 0;
	while (y < BOARD_SIZE)
	{
		x = 0;
		while (x < BOARD_SIZE)
		{
			if (board->b[y][x].pid == target)
			{
				tcoords->x = x;
				tcoords->y = y;
			}
			x++;
		}
		y++;
	}
}

t_s32			do_turn(
t_player *const p,
t_board *const board
)
{
	t_msg			msg;
	pid_t			target;
	t_player_coords	tcoords;

	if (msg_rcv(p, &msg) < 0 || unforge_msg(&msg, &target) < 0)
	{
		return (0);
	}
	else
	{
		if (find_target(target, board, &tcoords) < 0)
		{
			return (0);
		}
		do_move(p, board, &tcoords);
		return (0);
	}
}
