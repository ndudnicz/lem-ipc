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
#include <signal.h>
#include <time.h>

#include "board.h"
#include "play.h"
#include "libftasm.h"
#include "config_ipcs.h"
#include "error.h"
#include "mylimits.h"
#include "init_ipcs.h"
#include "signal_handler.h"
#include "clean_ipcs.h"

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
	return (i > 5 || ft_atoi(s) > USHORTMAX ? -1 : 0);
}

int				main(int ac, char **av)
{
	size_t		result;
	t_player	player;

	player.opt |= P_OPT_NEW;
	signal(SIGINT, signal_handler);
	if (ac != 2 || (int)(player.team = valid_team_number(av[1])) < 0)
	{
		exit(ft_error_ret("Error: ", INVALID_TEAM_NUMBER, NULL, EXIT_FAILURE));
	}
	else if (__builtin_mul_overflow(BOARD_SIZE, BOARD_SIZE, &result))
	{
		exit(ft_error_ret("Error: ", BOARD_SIZE_TOO_BIG, NULL, EXIT_FAILURE));
	}
	else
	{
		srand(time(NULL));
		init_ipcs(&player);
		lets_play(&player, NULL);
		clean_ipcs(&player);
		return (0);
	}
}
