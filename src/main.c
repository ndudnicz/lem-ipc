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
#include <stdio.h> //
#include <errno.h> //
#include <string.h> //

#include "libftasm.h"
#include "shm_config.h"
#include "error.h"
#include "mylimits.h"

static t_s32	valid_team_number(char const *const s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (ft_isdigit(s[i]) == 0)
		{
			return (-1);
		}
		i++;
	}
	return (i > 1 || ft_atoi(s) > 9 ? -1 : 0);
}

int				main(int ac, char **av)
{
	t_s32		shmid;
	size_t		result;

	if (ac != 2 || valid_team_number(av[1]) < 0)
	{
		exit(ft_error_ret("Error: ", INVALID_TEAM_NUMBER, NULL, EXIT_FAILURE));
	}
	if (__builtin_mul_overflow(BOARD_SIZE, BOARD_SIZE, &result))
	{
		exit(ft_error_ret("Error: ", BOARD_SIZE_TOO_BIG, NULL, EXIT_FAILURE));
	}
	if ((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_FLAG)) < 0)
	{
		exit(ft_error_ret("Error: ", FAIL_SHMGET, NULL, EXIT_FAILURE));
	}
	else
	{

		return (0);
	}
}
