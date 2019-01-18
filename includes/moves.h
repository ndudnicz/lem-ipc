/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 15:22:45 by ndudnicz          #+#    #+#             */
/*   Updated: 2019/01/18 15:22:46 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVES_H
# define MOVES_H

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
t_player_coords	tcoords
);

#endif
