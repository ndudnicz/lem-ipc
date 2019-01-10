#ifndef CHECK_SIDES_H
# define CHECK_SIDES_H

t_u32	check_left(
	t_player *p,
	t_board *board
);

t_u32	check_right(
	t_player *p,
	t_board *board
);

t_u32	check_up(
	t_player *p,
	t_board *board
);

t_u32	check_down(
	t_player *p,
	t_board *board
);

#endif
