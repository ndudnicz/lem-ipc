#include <stdlib.h>
#include <sys/msg.h>
#include <errno.h>

#include "libftasm.h"
#include "error.h"
#include "board.h"
#include "msg.h"

static t_s32	get_mtype(
t_player *const player
)
{
	return (player->team + 1);
}

t_s32			unforge_msg(
t_msg *const msg,
pid_t *const target
)
{
	*target = (pid_t)msg->mtext;
	return (0);
}

t_s32			forge_msg(
t_msg *const msg,
t_player *const player,
pid_t const target
)
{
	msg->mtype = (long)get_mtype(player);
	ft_memcpy(msg->mtext, &target, sizeof(pid_t));
	return (0);
}

t_s32			msg_send(
t_player *const player,
t_msg *const msg
)
{
	if ((msgsnd(player->ipcs.msgid, msg, MSGSIZE, 0)) < 0)
	{
		exit(ft_error_ret("Error: ", FAIL_MSGSND, NULL, EXIT_FAILURE));
	}
	else
	{
		return (0);
	}
}

t_s32			msg_rcv(
t_player *const player,
t_msg *const msg
)
{
	if ((msgrcv(player->ipcs.msgid, msg, MSGSIZE, get_mtype(player), RCV_FLAG)) < 0)
	{
		if (errno != ENOMSG)
		{
			exit(ft_error_ret("Error: ", FAIL_MSGRCV, NULL, EXIT_FAILURE));
		}
		else
		{
			return (0);
		}
	}
	else
	{
		return (0);
	}
}
