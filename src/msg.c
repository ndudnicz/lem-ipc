/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 15:01:14 by ndudnicz          #+#    #+#             */
/*   Updated: 2019/01/24 15:01:15 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>

#include "board.h"
#include "msg.h"
#include "clean_ipcs.h"
#include "error.h"

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
	msg->mtext[0] = target & 0xff;
	msg->mtext[1] = (target >> 8) & 0xff;
	msg->mtext[2] = (target >> 16) & 0xff;
	msg->mtext[3] = (target >> 24) & 0xff;
	return (0);
}

t_s32			msg_send(
t_player *const player,
t_msg *const msg
)
{
	if ((msgsnd(player->ipcs.msgid, msg, MSGSIZE, 0)) < 0)
	{
		(void)ctl_all(player);
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
	if ((long)(msgrcv(player->ipcs.msgid, msg, MSGSIZE,
	get_mtype(player), RCV_FLAG)) < 0)
	{
		if (errno && errno != ENOMSG)
		{
			(void)ctl_all(player);
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
