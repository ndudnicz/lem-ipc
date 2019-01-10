#ifndef PLAYER_H
# define PLAYER_H

# include "ipcs_config.h"

typedef struct	s_player
{
	t_u32			team;
	t_u16			x;
	t_u16			y;
	t_ipcs_config	ipcs;
}				t_player;

#endif
