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
#include <stdlib.h>
#include <stdio.h> //
#include <errno.h> //
#include <string.h> //

#include "libftasm.h"
#include "ipcs_config.h"
#include "error.h"
#include "mylimits.h"
#include "player.h"
#include "init_ipcs.h"

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
	size_t		result;
	t_player	player;

	if (ac != 2 || (player.team = valid_team_number(av[1])) < 0)
	{
		exit(ft_error_ret("Error: ", INVALID_TEAM_NUMBER, NULL, EXIT_FAILURE));
	}
	else if (__builtin_mul_overflow(BOARD_SIZE, BOARD_SIZE, &result))
	{
		exit(ft_error_ret("Error: ", BOARD_SIZE_TOO_BIG, NULL, EXIT_FAILURE));
	}
	else
	{
		init_ipcs(&player);
		clean_ipcs(&player);
		return (0);
	}
}
