#include <stdlib.h>

#include "mylimits.h"
#include "error.h"
#include "ipcs_config.h"
#include "player.h"

t_s32			init_ipcs(
	t_player *p
)
{
	if ((p->ipcs.shmid = shmget(SHM_KEY, SHM_SIZE, SHM_FLAG)) < 0)
	{
		exit(ft_error_ret("Error: ", FAIL_SHMGET, NULL, EXIT_FAILURE));
	}
	else if ((p->ipcs.semid = semget(SHM_KEY, 1, SEM_FLAG)) < 0)
	{
		exit(ft_error_ret("Error: ", FAIL_SEMGET, NULL, EXIT_FAILURE));
	}
	else if ((p->ipcs.msgid = msgget(SHM_KEY, MSG_FLAG)) < 0)
	{
		exit(ft_error_ret("Error: ", FAIL_MSGGET, NULL, EXIT_FAILURE));
	}
	else
	{
		return (0);
	}
}
