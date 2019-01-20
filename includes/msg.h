/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 15:27:37 by ndudnicz          #+#    #+#             */
/*   Updated: 2019/01/18 15:27:39 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSG_H
# define MSG_H

# include <sys/msg.h>

# define RCV_PERM	0660
# define RCV_FLAG	(IPC_NOWAIT | RCV_PERM)

typedef struct	s_msg
{
	long	mtype;
	char	mtext[sizeof(pid_t)];
}				t_msg;

# define MSGSIZE	(sizeof(pid_t))

t_s32			unforge_msg(
t_msg *const msg,
pid_t *const target
);

t_s32			forge_msg(
t_msg *const msg,
t_player *const player,
pid_t const target
);

t_s32			msg_send(
t_player *const player,
t_msg *const msg
);

t_s32			msg_rcv(
t_player *const player,
t_msg *const msg
);

#endif
