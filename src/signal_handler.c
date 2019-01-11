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

#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <stdlib.h>

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
		clean_ipcs(&p);
		exit(0);
	}
	else
	{
		return (0);
	}
}
