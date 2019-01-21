#include <stdio.h>

#include "board.h"

t_s32	this_is_the_end(
t_player *const p,
t_board *const board
)
{
	t_s32		x;
	t_s32		y;
	t_s32	others;

	puts("this_is_the_end");
	y = 0;
	while (y < BOARD_SIZE)
	{
		x = 0;
		while (x < BOARD_SIZE)
		{

			if (board->b[y][x].team >= 0 && board->b[y][x].team != p->team)
			{
				others = board->b[y][x].team;
			}
			if (others != board->b[y][x].team && board->b[y][x].team >= 0 && board->b[y][x].team != p->team)
				return (1);

			x++;
		}
		y++;
	}
	board->opt |= B_OPT_END;
				puts("B");
	return (1);
}

t_s32	i_win(
t_player *const p,
t_board *const board
)
{
	(void)player_suicide(p, board);
	printf("team %d win !\n", p->team);
	return (0);
}
