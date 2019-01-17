/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 16:14:05 by ndudnicz          #+#    #+#             */
/*   Updated: 2019/01/11 16:14:07 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "board.h"
#include "init_ipcs.h"
#include "clean_ipcs.h"

t_s32	signal_handler(
int sig
)
{
	t_player	p;

	puts("signal_handler");
	if (sig == SIGINT)
	{
		puts("A");
		init_ipcs(&p);
		puts("B");
		erase_player(getpid(), &p,  NULL);
		puts("C");
		player_suicide(&p, NULL);
		clean_ipcs(&p);
		puts("D");
		exit(EXIT_SUCCESS);
	}
	else
	{
		puts("E");
		return (0);
	}
}
