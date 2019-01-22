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

# define P_OPT_NEW		0x01

# define B_OPT_END		0x04

typedef struct	s_box
{
	pid_t	pid;
	t_u8	opt;
	t_s32	team;
}				t_box;

typedef struct	s_board
{
	t_u8	opt;
	t_u16	n_player;
	t_box	b[BOARD_SIZE][BOARD_SIZE];
}				t_board;


typedef t_u16	t_player_coords;

typedef struct	s_player
{
	t_s32			team;
	t_u16			x;
	t_u16			y;
	t_u16			prev_x;
	t_u16			prev_y;
	t_u8			opt;
	t_ipcs_config	ipcs;
	struct sembuf	sem;
}				t_player;

t_s32			player_suicide(
t_player *const p,
t_board *board
);

t_s32			spawn_on_board(
t_player *const p
);

#endif
