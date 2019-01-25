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

#include <stdlib.h>
#include <signal.h>

#include "board.h"
#include "play.h"
#include "libftasm.h"
#include "libft.h"
#include "mylimits.h"
#include "init_ipcs.h"
#include "signal_handler.h"
#include "clean_ipcs.h"
#include "error.h"

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
	return (i > 5 || ft_atoi(s) > USHORTMAX ? -1 : ft_atoi(s));
}

static void		error_main(
t_player **const player,
char const *const s1,
char const *const s2,
int const ret
)
{
	free(*player);
	*player = NULL;
	exit(ft_error_ret("Error: ", s1, s2, ret));
}

static t_s32	setup_signal(void)
{
	t_s32	i;

	i = 0;
	while (i < 64)
	{
		signal(i, signal_handler);
		i++;
	}
	return (0);
}

int				main(int ac, char **av)
{
	size_t		result;
	t_player	*player;

	if (BOARD_SIZE > 2000)
		exit(ft_error_ret("Error: ", BOARD_SIZE_TOO_BIG, NULL, EXIT_FAILURE));
	if ((player = (t_player*)ft_calloc(sizeof(t_player))) == NULL)
		exit(ft_error_ret("Error: ", FAIL_MALLOC, NULL, EXIT_FAILURE));
	(void)setup_signal();
	player->opt |= P_OPT_NEW;
	if (ac != 2 || (int)(player->team = valid_team_number(av[1])) < 0)
		error_main(&player, INVALID_TEAM_NUMBER, NULL, EXIT_FAILURE);
	else if (__builtin_mul_overflow(BOARD_SIZE, BOARD_SIZE, &result))
		error_main(&player, BOARD_SIZE_TOO_BIG, NULL, EXIT_FAILURE);
	else
	{
		(void)init_ipcs(player);
		(void)spawn_on_board(player);
		(void)lets_play(player, NULL);
		(void)clean_ipcs(player);
		free(player);
		return (0);
	}
}
