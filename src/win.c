#include <stdio.h>
#include <unistd.h>

#include "board.h"

t_s32	this_is_the_end(
t_player *const p,
t_board *const board
)
{
	t_s32		x;
	t_s32		y;
	t_s32		other;
	pid_t const	pid = getpid();

	puts("this_is_the_end()");
	y = 0;
	other = -1;
	while (y < BOARD_SIZE)
	{
		x = 0;
		while (x < BOARD_SIZE)
		{
			if (board->b[y][x].team >= 0 && board->b[y][x].pid != pid)
			{
				if (other == -1)
				{
					other = board->b[y][x].team;
				}
				else if (other != board->b[y][x].team)
				{
				puts("no");
					return (1);
				}
			}
			x++;
		}
		y++;
	}
	board->opt |= B_OPT_END;
				puts("yes");
	return (1);
}

t_s32	i_win(
t_player *const p,
t_board *const board
)
{
	printf("team %d win !\n", p->team);
	(void)player_suicide(p, board);
	return (0);
}
