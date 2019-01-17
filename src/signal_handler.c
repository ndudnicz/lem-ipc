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

	if (sig == SIGINT)
	{
		init_ipcs(&p);
		player_suicide(&p, NULL);
		clean_ipcs(&p);
		exit(0);
	}
	else
	{
		return (0);
	}
}
