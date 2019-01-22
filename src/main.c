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

// #include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
// #include <time.h>

#include "board.h"
#include "play.h"
#include "libftasm.h"
#include "libft.h"
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

int				main(int ac, char **av)
{
	size_t		result;
	t_player	*player;

	if ((player = (t_player*)ft_calloc(sizeof(t_player))) == NULL)
		exit(ft_error_ret("Error: ", FAIL_MALLOC, NULL, EXIT_FAILURE));
	player->opt |= P_OPT_NEW;
	signal(SIGINT, signal_handler);
	if (ac != 2 || (int)(player->team = valid_team_number(av[1])) < 0)
		error_main(&player, INVALID_TEAM_NUMBER, NULL, EXIT_FAILURE);
	else if (__builtin_mul_overflow(BOARD_SIZE, BOARD_SIZE, &result))
		error_main(&player, BOARD_SIZE_TOO_BIG, NULL, EXIT_FAILURE);
	else
	{
		puts("main A");
		(void)init_ipcs(player);
		puts("main B");
		(void)spawn_on_board(player);
		puts("main C");
		(void)lets_play(player, NULL);
		puts("main D");
		(void)clean_ipcs(player);
		puts("main E");
		free(player);
		return (0);
	}
}
