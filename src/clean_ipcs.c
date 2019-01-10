#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <stdlib.h>

#include "mylimits.h"
#include "player.h"

t_s32	clean_ipcs(
	t_player *p
)
{
	shmctl(p->ipcs.shmid, IPC_RMID, NULL); // del shm
	semctl(p->ipcs.semid, IPC_RMID, 0); // del sem
	msgctl(p->ipcs.msgid, IPC_RMID, 0); // del msg
	return (0);
}
