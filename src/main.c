/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 11:56:13 by ndudnicz          #+#    #+#             */
/*   Updated: 2018/12/14 11:56:14 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>

#include "libftasm.h"
#include "shm_config.h"
#include "error.h"

int		main(int ac, char **av)
{
	t_s32 const	shmflg = 0; /* shmflg to be passed to shmget() */
	t_s32		shmid; /* return value from shmget() */
	size_t		result;

	if (__builtin_mul_overflow(BOARD_SIZE, BOARD_SIZE, &result))
		exit(ft_error_ret("Error: " , BOARD_SIZE_TOO_BIG, NULL, EXIT_FAILURE));
	shmid = shmget(SHM_KEY, SHM_SIZE, shmflg);
	return (0);
}
