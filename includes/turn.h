#ifndef TURN_H
# define TURN_H

typedef struct	s_target_coord
{
	t_player_coords	x;
	t_player_coords	y;
}				t_target_coord;

t_s32	do_turn(
t_player *const p,
t_board *board
);

#endif
