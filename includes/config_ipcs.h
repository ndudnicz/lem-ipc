/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipcs_config.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 11:56:04 by ndudnicz          #+#    #+#             */
/*   Updated: 2018/12/14 11:56:05 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_IPCS_H
# define CONFIG_IPCS_H

# include <sys/ipc.h>
# include <sys/shm.h>

# define IPCS_KEY	0x00e1d220

# define SHM_SIZE	(sizeof(t_board))
# define SHM_PERM	0666
# define SHM_FLAG	(IPC_CREAT | SHM_PERM)
# define SHM_FLAG_F	(IPC_CREAT | IPC_EXCL | SHM_PERM)

# define SEM_PERM	0666
# define SEM_FLAG	(IPC_CREAT | IPC_EXCL | SEM_PERM)

# define MSG_PERM	0666
# define MSG_FLAG	(IPC_CREAT | IPC_EXCL | MSG_PERM)

# define SEMOP_TIMEOUT_VALUE	2

typedef struct	s_ipcs_config
{
	t_s32	shmid;
	t_s32	semid;
	t_s32	msgid;
}				t_ipcs_config;

#endif
