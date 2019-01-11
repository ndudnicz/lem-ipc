#ifndef BOARD_H
# define BOARD_H

# include "config.h"
# include "mystdint.h"

# if BOARD_SIZE <= 0
#  error BOARD_SIZE wrong value.
# elseif BOARD_SIZE > 2000
#  error BOARD_SIZE too high.
# endif

typedef struct	s_board
{
	t_u32	b[BOARD_SIZE][BOARD_SIZE];
}				t_board;

#endif
