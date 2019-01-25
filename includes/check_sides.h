/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sides.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 16:14:33 by ndudnicz          #+#    #+#             */
/*   Updated: 2019/01/11 16:14:35 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_SIDES_H
# define CHECK_SIDES_H

t_u32	check_left(
t_player const *const p,
t_board const *const b
);

t_u32	check_right(
t_player const *const p,
t_board const *const b
);

t_u32	check_up(
t_player const *const p,
t_board const *const b
);

t_u32	check_down(
t_player const *const p,
t_board const *const b
);

#endif
