#include <stdlib.h>

#include "board.h"
#include "player.h"

t_s32	player_suicide(
t_player *p
)
{
	t_board	*board;

	if ((int)(board = (t_board *)shmat(p->ipcs.shmid, NULL, 0)) < 0)
		exit(ft_error_ret("Error: ", FAIL_SHMAT, NULL, EXIT_FAILURE));
	else
	{
		board->n_player--;
		return (0);
	}

}
