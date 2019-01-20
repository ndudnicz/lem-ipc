#include <stdlib.h>
#include <sys/msg.h>
#include <errno.h>

#include "libftasm.h"
#include "error.h"
#include "board.h"
#include "msg.h"

#include <stdio.h>// // DEBUG
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
	*target = ((t_u8)msg->mtext[3] << 24) |
	((t_u8)msg->mtext[2] << 16) |
	((t_u8)msg->mtext[1] << 8) |
	(t_u8)msg->mtext[0];
	return (0);
}

t_s32			forge_msg(
t_msg *const msg,
t_player *const player,
pid_t const target
)
{
	msg->mtype = (long)get_mtype(player);
	puts("forge_msg()"); // DEBUG
	msg->mtext[0] = target & 0xff;
	msg->mtext[1] = (target >> 8) & 0xff;
	msg->mtext[2] = (target >> 16) & 0xff;
	msg->mtext[3] = (target >> 24) & 0xff;
	printf("msg->mtext: %x\n", ((t_u8)msg->mtext[3] << 24) | ((t_u8)msg->mtext[2] << 16) | ((t_u8)msg->mtext[1] << 8) | (t_u8)msg->mtext[0]); // DEBUG
	return (0);
}

t_s32			msg_send(
t_player *const player,
t_msg *const msg
)
{
	puts("msg_send()"); // DEBUG
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
	puts("msg_rcv()"); // DEBUG
	if ((long)(msgrcv(player->ipcs.msgid, msg, MSGSIZE,
	get_mtype(player), RCV_FLAG)) < 0)
	{
		if (errno && errno != ENOMSG)
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
