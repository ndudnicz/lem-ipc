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

#ifndef IPCS_CONFIG_H
# define IPCS_CONFIG_H

# include <sys/ipc.h>
# include <sys/shm.h>

# include "misc.h"
# include "config.h"
# include "error.h"

# define SHM_KEY	0x00e1d2f3

# define SHM_SIZE	(sizeof(t_board))
# define SHM_PERM	0660
# define SHM_FLAG	(IPC_CREAT | SHM_PERM)
# define SHM_FLAG_F	(IPC_CREAT | SHM_PERM | IPC_EXCL)

# define SEM_PERM	0660
# define SEM_FLAG	(IPC_CREAT | SEM_PERM)

# define MSG_PERM	0660
# define MSG_FLAG	(IPC_CREAT | MSG_PERM)

typedef struct	s_ipcs_config
{
	t_s32	shmid;
	t_s32	semid;
	t_s32	msgid;
}				t_ipcs_config;

#endif
