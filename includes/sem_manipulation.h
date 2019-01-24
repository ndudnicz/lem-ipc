/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_manipulation.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 15:03:09 by ndudnicz          #+#    #+#             */
/*   Updated: 2019/01/24 15:03:11 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEM_MANIPULATION_H
# define SEM_MANIPULATION_H

t_s32	lock_sem(
t_player *const p,
int semflag
);

t_s32	release_sem(
t_player *const p,
t_board **board
);

#endif
