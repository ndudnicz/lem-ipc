/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 15:28:03 by ndudnicz          #+#    #+#             */
/*   Updated: 2019/01/18 15:28:04 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TURN_H
# define TURN_H

typedef struct	s_target_coord
{
	t_player_coords	x;
	t_player_coords	y;
}				t_target_coord;

t_s32			do_turn(
t_player *const p,
t_board *const board
);

typedef t_s32	(*t_move)(t_player*const, t_board*const);

t_s32	move_up(
t_player *const p,
t_board *const board
);

t_s32	move_down(
t_player *const p,
t_board *const board
);

t_s32	move_left(
t_player *const p,
t_board *const board
);

t_s32	move_right(
t_player *const p,
t_board *const board
);

t_s32	do_move(
t_player *const p,
t_board *const board,
t_target_coord *const tcoords
);

#endif
