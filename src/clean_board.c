#include <unistd.h>
#include <stdlib.h>

#include "mystdint.h"
#include "board.h"
#include "print.h"

t_s32	clean_pid(
pid_t pid,
t_board *board
)
{
	t_s32			x;
	t_s32			y;

	y = 0;
	puts("clean_pid()");//
	ft_memset(board, 0, sizeof(t_board));
	while (y < BOARD_SIZE)
	{
		x = 0;
		while (x < BOARD_SIZE)
		{
			if (board->b[y][x].pid == pid)
			{
				board->b[y][x].pid = 0;
				board->b[y][x].team = -1;
				if (board->b[y][x].opt & P_OPT_PRINTER)
					unset_printer(NULL, board);
			}
			x++;
		}
		y++;
	}
	return (0);
}

t_s32	erase_player(
pid_t pid,
t_player *p,
t_board *board
)
{
	puts("erase_player()");
	if (board == NULL)
	{
		ft_memset(&p->sem, 0, sizeof(struct sembuf));
		p->sem.sem_op = -1;
		semop(p->ipcs.semid, &p->sem, 1);
		if ((int)(board = (t_board *)shmat(p->ipcs.shmid, NULL, 0)) < 0)
			exit(ft_error_ret("Error: ", FAIL_SHMAT, NULL, EXIT_FAILURE));
		else
		{
			clean_pid(pid, board);
			shmdt(board);
			board = NULL;
			p->sem.sem_op = 1;
			semop(p->ipcs.semid, &p->sem, 1);
		}
	}
	else
	{
		clean_pid(pid, board);
	}
	return (0);
}
