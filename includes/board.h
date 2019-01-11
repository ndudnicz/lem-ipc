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

# if BOARD_SIZE <= 0
#  error BOARD_SIZE wrong value.
# elseif BOARD_SIZE > 2000
#  error BOARD_SIZE too high.
# endif

typedef struct	s_board
{
	t_u16	n_player;
	t_s32	b[BOARD_SIZE][BOARD_SIZE];
}				t_board;

#endif