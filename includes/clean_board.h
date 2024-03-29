/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_board.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 18:05:44 by ndudnicz          #+#    #+#             */
/*   Updated: 2019/01/17 18:05:45 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEAN_BOARD_H
# define CLEAN_BOARD_H

t_s32	clean_pid(
pid_t const pid,
t_board *const board
);

t_s32	erase_player(
pid_t const pid,
t_player *const p,
t_board *const board
);

#endif
