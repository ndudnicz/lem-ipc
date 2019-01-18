#include <stdio.h>
//
#include "board.h"
void print_debug(t_player*p,t_board*b)
{
	printf("DEBUG-------->\n");
	if (p)
	{
	printf("player->team: %d\n", p->team);
	printf("player->opt: %x\n", p->opt);
	printf("player->x: %d\nplayer->y: %d\n", p->x, p->y);

	}
	else
	{
	printf("player: null\n");
	}

	if (b)
	{
	printf("board->opt: %p\n", b ? b->opt : b);
	printf("board->n_player: %d\n", b != NULL? b->n_player :b);

	}
	else
	{
	printf("board: null\n");
	}
	printf("DEBUG--------<\n");
}
