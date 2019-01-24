#include <sys/sem.h>
#include <stdlib.h>
#include <stdio.h>//

#include "board.h"
#include "mystdint.h"

t_s32	release_sem(
t_player *const p,
t_board **board
)
{
	puts("release sem");
	shmdt(*board);
	*board = NULL;
	p->sem.sem_op = 1;
	semop(p->ipcs.semid, &p->sem, 1);
	return (0);
}
