/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 16:15:42 by ndudnicz          #+#    #+#             */
/*   Updated: 2019/01/11 16:15:43 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "config_ipcs.h"
# include <sys/sem.h>

# define P_OPT_NEW		0x01
# define P_OPT_PRINTER	0x02

typedef struct	s_player
{
	t_u32			team;
	t_u16			x;
	t_u16			y;
	t_u8			opt;
	t_ipcs_config	ipcs;
	struct sembuf	sem;
}				t_player;

t_s32	player_suicide(
t_player *p
);

#endif
