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

# include "ipcs_config.h"

typedef struct	s_player
{
	t_u32			team;
	t_u16			x;
	t_u16			y;
	t_u8			new;
	t_ipcs_config	ipcs;
}				t_player;

#endif
