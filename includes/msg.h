#ifndef MSG_H
# define MSG_H

# define MSGSIZE	(sizeof(pid_t))

typedef struct	s_msg
{
	long	mtype;
	char	mtext[MSGSIZE];
}				t_msg;

t_s32	unforge_msg(
t_msg *const msg,
pid_t *const target
);

t_s32	forge_msg(
t_msg *const msg,
t_player *const player,
pid_t const target
);

t_s32	msg_send(
t_player *const player,
t_msg *const msg
);

t_s32	msg_rcv(
t_player *const player,
t_msg *const msg
);

#endif
