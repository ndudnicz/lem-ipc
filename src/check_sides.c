t_u32	check_left(
	t_player *p,
	t_board *board
)
{
	if (p->x > 0)
	{
		return (board->b[p->y][p->x - 1]);
	}
	else
	{
		return (0);
	}
}

t_u32	check_right(
	t_player *p,
	t_board *board
)
{
	if (p->x < BOARD_SIZE)
	{
		return (board->b[p->y][p->x + 1]);
	}
	else
	{
		return (0);
	}
}

t_u32	check_up(
	t_player *p,
	t_board *board
)
{
	if (p->x > 0)
	{
		return (board->b[p->y - 1][p->x]);
	}
	else
	{
		return (0);
	}
}

t_u32	check_down(
	t_player *p,
	t_board *board
)
{
	if (p->x < BOARD_SIZE)
	{
		return (board->b[p->y + 1][p->x]);
	}
	else
	{
		return (0);
	}
}
