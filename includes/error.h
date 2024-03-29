/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 16:15:09 by ndudnicz          #+#    #+#             */
/*   Updated: 2019/01/11 16:15:10 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "mystdint.h"

# define BOARD_SIZE_TOO_BIG "BOARD_SIZE too big.\n"
# define INVALID_TEAM_NUMBER "Invalid team number.\n"
# define TOO_MANY_PLAYER "Too many players on the field.\n"
# define FAIL_SHMGET "Can't shmget().\n"
# define FAIL_SEMGET "Can't semget().\n"
# define FAIL_MSGGET "Can't msgget().\n"
# define FAIL_SHMAT "Can't shmat().\n"
# define FAIL_MALLOC "Can't malloc().\n"
# define FAIL_MSGSND "Can't msgsnd().\n"
# define FAIL_MSGRCV "Can't msgrcv().\n"
# define SEMOP_TIMEOUT "semop() timeout.\n"

t_s32	ft_error_ret(
char const *const s1,
char const *const s2,
char const *const s3,
t_s32 const ret
);

#endif
