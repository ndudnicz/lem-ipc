/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 16:14:18 by ndudnicz          #+#    #+#             */
/*   Updated: 2019/01/11 16:14:20 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOARD_H
# define BOARD_H

# include "config.h"
# include "mystdint.h"
# include "config_ipcs.h"
# include <sys/sem.h>

# if BOARD_SIZE <= 0
#  error BOARD_SIZE wrong value.
# elseif BOARD_SIZE > 2000
#  error BOARD_SIZE too high.
# endif

# define B_OPT_PRINTER	P_OPT_PRINTER

typedef struct	s_board
{
	t_u8	opt;
	t_u16	n_player;
	t_s32	b[BOARD_SIZE][BOARD_SIZE];
}				t_board;

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
t_player *p,
t_board *board
);

#endif
